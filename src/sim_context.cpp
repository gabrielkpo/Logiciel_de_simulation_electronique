#include "sim_context.hpp"

SimContext createSimContext(Circuit &circuit, const Source &source, double R2) {
    SimContext ctx;
    ctx.x1 = 0.0;
    ctx.x2 = 0.0;

    // Capture circuit and source by reference (they live in the caller),
    // but capture R2 by value to avoid a dangling reference after return.
    ctx.f1 = [&circuit, &source, R2](double t, double vs)->double {
        double ve = source.ve(t);
        return circuit.deriv1(t, vs, ve, R2);
    };

    ctx.f2_1 = [&circuit, &source](double t, double x1, double x2)->double {
        double ve = source.ve(t);
        double dx1, dx2;
        circuit.deriv2(t, x1, x2, ve, dx1, dx2);
        return dx1;
    };

    ctx.f2_2 = [&circuit, &source](double t, double x1, double x2)->double {
        double ve = source.ve(t);
        double dx1, dx2;
        circuit.deriv2(t, x1, x2, ve, dx1, dx2);
        return dx2;
    };

    return ctx;
}
