library(here)

DATA_DIR <- here::here("data")

RNGS <- c(
  "mersenne-twister-19937",
  "mersenne-twister-19937-64",
  "ranlux24_base",
  "ranlux48_base",
  "ranlux24",
  "ranlux48",
  "knuth_b",
  "minstd_rand",
#  "minstd_rand0",

  "b_mersenne-twister-19937",
  "b_mersenne-twister-19937-64",
  "b_ranlux3",
  "ranlux64_3",
  "b_rand48",
  "b_sobol",
  "b_ecuyer1988",
  "b_kreutzer1986",
  "b_taus88",
  "b_hellekalek1995",
  "b_mt11213b",
  "b_lagged_fibonacci607",
  "b_lagged_fibonacci44497",
  "b_minstd_rand",
  "b_minstd_rand0"

)

OPTIM_PROBLEMS <- c(
  "sphere",
  "rosenbrock",
  "ellips",
  "schwefel",
  "ackley",
  "rastrigin"
)

DIMENSIONS <- c(10, 30, 50)

REP_NUM <- 20

