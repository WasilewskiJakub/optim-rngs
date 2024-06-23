#pragma once

#include <cmath>
#include <functional>
#include <string>

using eval_func = std::function<double(const double *, const int)>;

struct optim_problem {
  optim_problem(std::string name, eval_func fn)
      : name_{std::move(name)}, fn_{fn} {}
  auto operator()(auto &&...args) { return fn_(args...); }
  std::string name_{};
  eval_func fn_{};
};

const auto sphere = optim_problem{"sphere", [](const double *x, const int N) {
                                    double val = 0.0;
                                    for (int i = 0; i < N; i++)
                                      val += x[i] * x[i];
                                    return val;
                                  }};

const auto rosenbrock =
    optim_problem("rosenbrock", [](const double *x, const int N) {
      double val = 0.0;
      for (int i = 0; i < N - 1; i++) {
        val += 100.0 * std::pow((x[i + 1] - x[i] * x[i]), 2) +
               std::pow((x[i] - 1.0), 2);
      }
      return val;
    });

const auto ellips = optim_problem("ellips", [](const double *x, const int N) {
  double val = 0.0;
  for (int i = 1; i <= N; i++)
    val += std::pow(1e6, (i - 1) / (N - 1)) * x[i - 1] * x[i - 1];
  return val;
});

const auto schwefel =
    optim_problem("schwefel", [](const double *x, const int N) {
      double val = 0.0;
      for (int i = 0; i < N; i++) {
        double ival = 0.0;
        for (int j = 0; j < i; j++)
          ival += x[j];
        val += ival * ival;
      }
      return val;
    });

const auto ackley = optim_problem("ackley", [](const double *x, const int N) {
  double val = 0.0, isum = 0.0, icos = 0.0;
  for (int i = 0; i < N; i++) {
    isum += x[i] * x[i];
    icos += std::cos(2.0 * M_PI * x[i]);
  }
  val = -20.0 *
            std::exp(-0.2 * std::sqrt((1.0 / static_cast<double>(N)) * isum)) -
        std::exp((1.0 / static_cast<double>(N)) * icos) + 20.0 + std::exp(1);
  return val;
});

const auto rastrigin =
    optim_problem("rastrigin", [](const double *x, const int N) {
      static double A = 10.0;
      double val = A * N;
      for (int i = 0; i < N; i++)
        val += x[i] * x[i] - A * cos(2 * M_PI * x[i]);
      return val;
    });

const auto OPTIM_PROBLEMS = std::array<optim_problem, 6>{sphere, rosenbrock, ellips, schwefel, ackley, rastrigin};
