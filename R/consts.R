library(here)

DATA_DIR <- here::here("data")

RNGS <- c(
  "mersenne-twister-19937",
  "mersenne-twister-19937-64",
  "ranlux24-base",
  "ranlux48-base",
  "ranlux24",
  "ranlux48",
  "knuth-b",
  "minstd-rand",
  "minstd-rand0"
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

