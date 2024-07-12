#ifndef SOBOL_RNG_HPP
#define SOBOL_RNG_HPP

#include <boost/random/sobol.hpp>

template <int Dimension>
struct sobol_d {
    using result_type = boost::random::sobol::result_type;
    
    boost::random::sobol rng;

    // Konstruktor domyślny
    sobol_d() : rng(Dimension) {}

    // Konstruktor z seedem
    sobol_d(unsigned int s) : rng(Dimension) {
        rng.seed(s);
    }

    // Generowanie następnej liczby
    auto operator()() {
        return rng();
    }

    // Resetowanie generatora
    void seed(unsigned int s) {
        rng.seed(s);
    }

    // Resetowanie generatora za pomocą generatora losowego
    template <typename Generator>
    void seed(Generator& gen) {
        rng.seed(gen);
    }

    // Uzyskanie minimalnej wartości możliwej do wygenerowania
    static constexpr result_type min() {
        return boost::random::sobol::min();
    }

    // Uzyskanie maksymalnej wartości możliwej do wygenerowania
    static constexpr result_type max() {
        return boost::random::sobol::max();
    }
};

#endif // SOBOL_RNG_HPP
