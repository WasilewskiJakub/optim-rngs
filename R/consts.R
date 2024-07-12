library(here)

DATA_DIR <- here::here("data")

RNGS <- c(
        "mersenne-twister-19937"
        ,"b_lagged-fibonacci1279"
        ,"b_lagged-fibonacci2281"
        ,"b_lagged-fibonacci3217"
        ,"b_lagged-fibonacci4423"
        ,"b_lagged-fibonacci9689"
        ,"b_lagged-fibonacci19937"
        ,"b_lagged-fibonacci23209"
        ,"b_ranlux4"
        ,"b_ranlux64_4"
        ,"b_ranlux3_01"
        ,"b_ranlux4_01"
        ,"b_ranlux64_3_01"
        ,"b_ranlux64_4_01"
        ,"mersenne-twister-19937-64"
        ,"ranlux24_base"
        ,"ranlux48_base"
        ,"ranlux24"
        ,"ranlux48"
        ,"knuth_b"
        ,"minstd_rand"
        ,"minstd_rand0"
        ,"b_mersenne-twister-19937"
        ,"b_mersenne-twister-19937-64"
        ,"b_minstd_rand"
        ,"b_minstd_rand0"
        ,"b_rand48"
        ,"b_ecuyer1988"
        ,"b_kreutzer1986"
        ,"b_taus88"
        ,"b_hellekalek1995"
        ,"b_mt11213b"
        ,"b_lagged_fibonacci607"
        ,"b_lagged_fibonacci44497"
        ,"b_ranlux3"
        ,"b_ranlux64_3"
        ,"b_sobol"
)

OPTIM_PROBLEMS <- c(
  "sphere",
  "rosenbrock",
  "ellips",
  "schwefel",
  "ackley",
  "rastrigin"
)

DIMENSIONS <- c(
10
# ,30
# ,50
)



REP_NUM <- 20

