# Lista pakietów do zainstalowania
packages <- c("dplyr","readr","purrr", "stringr", "tibble", "glue", "here","ggplot2","scales","gghighlight")

# Funkcja do instalacji brakujących pakietów
install_if_missing <- function(pkg) {
  if (!requireNamespace(pkg, quietly = TRUE)) {
    install.packages(pkg)
  }
}

# Instalacja brakujących pakietów
invisible(lapply(packages, install_if_missing))

# Ładowanie pakietów
lapply(packages, library, character.only = TRUE)

# Sprawdzenie, czy pakiety są załadowane
loaded_packages <- sapply(packages, require, character.only = TRUE)
print(loaded_packages)
