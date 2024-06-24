library(dplyr)
library(readr)
library(purrr)
library(stringr)
library(tibble)
library(glue)
library(here)

source(here::here("R", "consts.R"))

exp_grid <- expand.grid(
  rng = RNGS,
  problem = OPTIM_PROBLEMS,
  dim = DIMENSIONS,
  rep = 1:REP_NUM
)

raw_dfr <- exp_grid %>%
  purrr::pmap(function(rng, problem, dim, rep) {
    fname = glue::glue("{DATA_DIR}/exp-{rng}-fn-{problem}-dim-{dim}-rep-{rep}.csv")
    readr::read_csv(fname, show_col_types=FALSE) %>%
      dplyr::mutate(rng=rng, dim=dim, rep=rep, fn=problem)
  }) %>%
  purrr::reduce(dplyr::bind_rows)


avg_dfr = raw_dfr %>% 
  dplyr::group_by(rng, fn, dim) %>%
  dplyr::group_map(function(data, group) {
    rep_num = max(data$rep)
    split(data, data$rep) %>%
      purrr::reduce(function(lhs, rhs) { (lhs + rhs) }) %>%
      dplyr::transmute(iter = iter / rep_num, best_value = best_value / rep_num, group) %>%
      tibble::tibble()
  }) %>% 
  purrr::reduce(dplyr::bind_rows)

readr::write_csv(avg_dfr, glue::glue("{DATA_DIR}/averaged-results.csv"))
