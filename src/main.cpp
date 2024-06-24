#include <cstdlib>
#include <random>
#include <range/v3/all.hpp>
#include <range/v3/view/iota.hpp>
#include <thread>
#include <type_traits>

#include "problem.hpp"
#include "util.hpp"

namespace rv = ranges::views;

template <typename RandomGenerator, int Dim, int RepNum>
void invoke_optimizer(std::string_view exp_name, auto &&eval_func,
                      const auto &seeds) {
  const auto x0 = std::vector<double>(Dim, 100.0);
  auto rep_seq = rv::closed_iota(1, RepNum);
  for (const auto &[seed, rep] : rv::zip(seeds, rep_seq)) {
    auto log_filename = fmt::format("exp-{}-fn-{}-dim-{}-rep-{}.csv", exp_name,
                                    eval_func.name_, Dim, rep);
    auto logger = logger_factory(log_filename);
    fmt::println(
        "[dim={}, fn={}, seed={}] Running {}-th repetition of experiment {}",
        Dim, eval_func.name_, seed, rep, exp_name);

    auto optimizer =
        vanila_cmaes_factory<RandomGenerator>(x0, eval_func, seed, logger);
    optimizer.optimize();
  }
  fmt::println("[dim={}, fn={}] Experiment {} finished.", Dim, eval_func.name_,
               exp_name);
}

template <typename T> struct rng_t {
  using RngType = T;
  std::string_view name_{};
};

template <int Dim, int RepNum, typename Rngs>
auto run_exps(const auto &seeds, const auto &problems, Rngs rngs) {
  constexpr auto rngs_num = std::make_index_sequence<std::tuple_size_v<Rngs>>{};
  run_exps_impl<Dim, RepNum>(seeds, problems, rngs, rngs_num);
}

template <int Dim, int RepNum, typename Rngs, std::size_t... Idxs>
auto run_exps_impl(const auto &seeds, const auto &problems, Rngs rngs,
                   std::index_sequence<Idxs...>) {
  auto do_exp = [&](const auto &rng) {
    using rng_type = std::decay_t<decltype(rng)>::RngType;
    for (const auto &p : problems) {
      invoke_optimizer<rng_type, Dim, RepNum>(rng.name_, p, seeds);
    }
  };

  (do_exp(std::get<Idxs>(rngs)), ...);
}

int main() {
  try {
    constexpr auto REP{20};
    const auto rngs =
        std::tuple{rng_t<std::mt19937>{"mersenne-twister-19937"},
                   rng_t<std::mt19937_64>{"mersenne-twister-19937-64"},
                   rng_t<std::ranlux24_base>{"ranlux24_base"},
                   rng_t<std::ranlux48_base>{"ranlux48_base"},
                   rng_t<std::ranlux24>{"ranlux24"},
                   rng_t<std::ranlux48>{"ranlux48"},
                   rng_t<std::knuth_b>{"knuth_b"},
                   rng_t<std::minstd_rand>{"minstd_rand"},
                   rng_t<std::minstd_rand0>{"minstd_rand0"}};
    auto seeds = rv::closed_iota(1, REP);

    auto dim10 =
        std::jthread{[&] { run_exps<10, REP>(seeds, OPTIM_PROBLEMS, rngs); }};
    auto dim30 =
        std::jthread{[&] { run_exps<30, REP>(seeds, OPTIM_PROBLEMS, rngs); }};
    auto dim50 =
        std::jthread{[&] { run_exps<50, REP>(seeds, OPTIM_PROBLEMS, rngs); }};

  } catch (std::exception &e) {
    fmt::println("{}", e.what());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
