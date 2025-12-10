#include "sim_context.hpp"

SimContext createSimContext(Circuit &circuit, const Source &source, double R2) {
    SimContext ctx;
    ctx.x1 = 0.0;
    ctx.x2 = 0.0;

    ctx.f1 = [&](double t, double vs)->double {
        double ve = source.getValue(t);
        return circuit.deriv1(t, vs, ve, R2);
    };

    ctx.f2_1 = [&](double t, double x1, double x2)->double {
        double ve = source.getValue(t);
        double dx1, dx2;
        circuit.deriv2(t, x1, x2, ve, dx1, dx2);
        return dx1;
    };

    ctx.f2_2 = [&](double t, double x1, double x2)->double {
        double ve = source.getValue(t);
        double dx1, dx2;
        circuit.deriv2(t, x1, x2, ve, dx1, dx2);
        return dx2;
    };

    return ctx;
}
