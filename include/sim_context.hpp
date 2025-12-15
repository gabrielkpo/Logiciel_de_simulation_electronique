#ifndef SIM_CONTEXT_HPP
#define SIM_CONTEXT_HPP

#include <functional>
#include "source.hpp"
#include "circuit.hpp"

// Petite structure qui contient l'état de simulation et les wrappers
struct SimContext {
    double x1 = 0.0;
    double x2 = 0.0;

    // f1 : (t, vs) -> dx1  (pour circuits ordre 1)
    std::function<double(double,double)> f1;

    // f2_1, f2_2 : (t, x1, x2) -> dx1/dx2 (pour circuits ordre 2)
    std::function<double(double,double,double)> f2_1;
    std::function<double(double,double,double)> f2_2;
};

// Factory : construit un SimContext en reliant le circuit et la source
SimContext createSimContext(Circuit &circuit, const Source &source, double R2);

#endif // SIM_CONTEXT_HPP
