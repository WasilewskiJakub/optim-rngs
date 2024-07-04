library(readr)
library(dplyr)
library(ggplot2)
library(glue)
library(here)
library(scales)
library(gghighlight)

source(here::here("R", "consts.R"))

AVG_DFR <- readr::read_csv(glue::glue("{DATA_DIR}/exp-3-avg/averaged-results.csv"), show_col_types=FALSE)

help = function() {
  print("Usage: Rscript generate-plots.R <function-name>")
  print(OPTIM_PROBLEMS)
}

# args <- commandArgs(trailingOnly = TRUE)
#
# if (length(args) != 1) {
#   help()
#   stop(1)
# }
#
# if (!(args[1] %in% OPTIM_PROBLEMS)) {
#   help()
#   stop(1)
# }


mk_plot <- function(dfx, fn_name, dimx, selected_rngs) {
  dfx %>% 
  dplyr::filter(fn == fn_name, dim == dimx) %>%
  ggplot2::ggplot() + 
  ggplot2::geom_line(aes(x=iter, y=best_value, col=rng)) + 
  gghighlight::gghighlight(rng %in% selected_rngs) + 
  ggplot2::scale_y_log10(
    breaks=trans_breaks("log10", function(x) 10^x, n = 20),
    labels=trans_format("log10", math_format(10^.x)),
  ) + 
  ggplot2::theme_bw() + 
  ggplot2::theme(
    axis.title = ggplot2::element_text(size = 25, face = "bold"),
    axis.text = ggplot2::element_text(size = 25, face = "bold"),
    legend.text = ggplot2::element_text(size = 25, face = "bold"),
    legend.title = ggplot2::element_text(size = 25, face = "bold"),
  )

}

