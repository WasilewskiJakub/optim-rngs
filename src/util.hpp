#pragma once

#include <libcmaes/cmasolutions.h>
#include <libcmaes/cmastrategy.h>
#include <libcmaes/covarianceupdate.h>
#include <libcmaes/esoptimizer.h>

#include <fmt/base.h>
#include <fmt/format.h>
#include <fmt/os.h>

#include "const.hpp"

template <typename RandomGenerator>
auto vanila_cmaes_factory(const auto &input, auto &&eval_func, const int seed,
                          auto &&logger_func) {
  using namespace libcmaes;
  const auto sigma = 1.0;
  auto params = CMAParameters<>{input, sigma};
  params.set_seed(seed);
  params.set_max_iter(100 * input.size());

  params.set_stopping_criteria(STAGNATION, false);
  params.set_stopping_criteria(TOLX, false);
  params.set_stopping_criteria(CONDITIONCOV, false);
  params.set_stopping_criteria(AUTOMAXITER, false);
  params.set_stopping_criteria(TOLHISTFUN, false);
  params.set_stopping_criteria(EQUALFUNVALS, false);
  params.set_stopping_criteria(TOLUPSIGMA, false);
  params.set_stopping_criteria(CONDITIONCOV, false);
  params.set_stopping_criteria(NOEFFECTAXIS, false);
  params.set_stopping_criteria(NOEFFECTCOOR, false);
  params.set_stopping_criteria(MAXFEVALS, false);
  params.set_stopping_criteria(FTARGET, false);

  params.set_stopping_criteria(MAXITER, true);

  auto optimizer =
      ESOptimizer<CMAStrategy<CovarianceUpdate, GenoPheno<NoBoundStrategy>,
                              RandomGenerator>,
                  CMAParameters<GenoPheno<NoBoundStrategy>>, CMASolutions>{
          eval_func, params};

  optimizer.set_plot_func(logger_func);

  return optimizer;
}

inline auto logger_factory(const std::filesystem::path &logfile) {
  using namespace libcmaes;
  auto fullpath = LOG_DIR / logfile;
  auto output = fmt::output_file(fullpath.string(), fmt::file::CREATE |
                                                        fmt::file::WRONLY |
                                                        fmt::file::APPEND);
  output.print("iter,sigma,best_value\n");
  return [fullpath](const CMAParameters<> &params,
                    const CMASolutions &solutions, auto &_) mutable -> int {
    auto output = fmt::output_file(fullpath.string(), fmt::file::CREATE |
                                                          fmt::file::WRONLY |
                                                          fmt::file::APPEND);
    output.print("{},{},{}\n", solutions.niter(), solutions.sigma(),
                 solutions.get_best_seen_candidate().get_fvalue());
    return 0;
  };
}
