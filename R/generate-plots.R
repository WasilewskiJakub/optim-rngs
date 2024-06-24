library(readr)
library(dplyr)
library(ggplot2)
library(glue)
library(here)

source(here::here("R", "consts.R"))

AVG_DFR <- readr::read_csv(glue::glue("{DATA_DIR}/averaged-results.csv"), show_col_types=FALSE)

help = function() {
  print("Usage: Rscript generate-plots.R <function-name>")
  print(OPTIM_PROBLEMS)
}

args <- commandArgs(trailingOnly = TRUE)

if (length(args) != 1) {
  help()
  stop(1)
}

if (!(args[1] %in% OPTIM_PROBLEMS)) {
  help()
  stop(1)
}

AVG_DFR %>% 
  dplyr::filter(fn == args[1]) %>%
  ggplot2::ggplot(aes(x=iter, y=best_value, col=rng)) + 
  ggplot2::geom_line() + 
  ggplot2::scale_y_log10() + 
  ggplot2::facet_wrap(~dim, ncol=1) + 
  ggplot2::theme_bw()
