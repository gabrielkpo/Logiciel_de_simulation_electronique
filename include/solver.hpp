#ifndef SOLVER_HPP
#define SOLVER_HPP
#include <functional>
using Deriv1 = std::function<double(double, double)>;
using Deriv2 = std::function<double(double, double, double)>;

// On définit les fonctions de résolution d'équations différentielles

// Euler simple pour circuits 1er ordre (CircuitA, CircuitB)

void euler1(double& x, double dt, double t, Deriv1 f);

// Euler pour systèmes 2x2 (circuits 2ème ordre) 

void euler2(double& x1, double& x2, double dt, double t, Deriv2 f1, Deriv2 f2);

// Runge-Kutta 4ème ordre pour systèmes 2x2

// Runge-Kutta 4ème ordre pour systèmes 2x2
void rk4(double& x1, double& x2, double dt, double t, Deriv2 f1, Deriv2 f2);

// Heun (Euler amélioré) pour systèmes 2x2
void heun(double& x1, double& x2, double dt, double t, Deriv2 f1, Deriv2 f2);

// --- Méthodes pour systèmes d'ordre 1 ---

// Runge-Kutta 4 pour l'ordre 1
void rk4_order1(double& x, double dt, double t, Deriv1 f);

// Heun pour l'ordre 1
void heun_order1(double& x, double dt, double t, Deriv1 f);

#endif