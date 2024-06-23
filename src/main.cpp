#include <cstdlib>
#include <random>
#include <range/v3/all.hpp>
#include <range/v3/view/iota.hpp>
#include <thread>

#include "problem.hpp"
#include "util.hpp"

template <typename RandomGenerator, int DIM, int REP>
void do_exp(std::string_view exp_name, auto &&eval_func) {
  const auto x0 = std::vector<double>(DIM, 100.0);
  for (const auto &rep : ranges::views::closed_iota(1, REP)) {
    auto log_filename = fmt::format("exp-{}-fn-{}-dim-{}-rep-{}.csv", exp_name,
                                    eval_func.name_, DIM, rep);
    auto logger = logger_factory(log_filename);
    fmt::println("[dim={}, fn={}] Running {}-th repetition of experiment {}",
                 DIM, eval_func.name_, rep, exp_name);

    auto optimizer =
        vanila_cmaes_factory<RandomGenerator>(x0, eval_func, logger);
    optimizer.optimize();
  }
  fmt::println("[dim={}, fn={}] Experiment {} finished.", DIM, eval_func.name_,
               exp_name);
}

template <int DIM, int REP> auto run_experiments(auto &&optim_problem) {
  do_exp<std::mt19937, DIM, REP>("mersenne-twister-19937", optim_problem);
  do_exp<std::mt19937_64, DIM, REP>("mersenne-twister-19937-64", optim_problem);
  do_exp<std::ranlux24_base, DIM, REP>("ranlux24-base", optim_problem);
  do_exp<std::ranlux48_base, DIM, REP>("ranlux48-base", optim_problem);
  do_exp<std::ranlux24, DIM, REP>("ranlux24", optim_problem);
  do_exp<std::ranlux48, DIM, REP>("ranlux48", optim_problem);
  do_exp<std::knuth_b, DIM, REP>("knuth-b", optim_problem);
  do_exp<std::minstd_rand, DIM, REP>("minstd-rand", optim_problem);
  do_exp<std::minstd_rand0, DIM, REP>("minstd-rand0", optim_problem);
}

int main(int argc, char *argv[]) {
  try {
    auto dim10 = std::jthread{[] {
      ranges::for_each(OPTIM_PROBLEMS,
                       [](auto &&p) { run_experiments<10, 20>(p); });
    }};

    auto dim30 = std::jthread{[] {
      ranges::for_each(OPTIM_PROBLEMS,
                       [](auto &&p) { run_experiments<30, 20>(p); });
    }};

    auto dim50 = std::jthread{[] {
      ranges::for_each(OPTIM_PROBLEMS,
                       [](auto &&p) { run_experiments<50, 20>(p); });
    }};

  } catch (std::exception &e) {
    fmt::println("{}", e.what());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
