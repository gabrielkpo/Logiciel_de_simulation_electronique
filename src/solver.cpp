#include "solver.hpp"

// Euler simple pour circuits 1er ordre (CircuitA, CircuitB)

void euler1(double& x, double dt, double t, Deriv1 f) {
    double dx_dt = f(t, x);
    x += dt * dx_dt;
}

// Euler pour systèmes 2x2 (circuits 2ème ordre)

void euler2(double& x1, double& x2, double dt, double t,
           Deriv2 f1,
           Deriv2 f2) {

    // Calcul des dérivées au point actuel

    double dx1_dt = f1(t, x1, x2);
    double dx2_dt = f2(t, x1, x2);
    
    // Mise à jour selon la méthode d'Euler

    x1 += dt * dx1_dt;
    x2 += dt * dx2_dt;
}

// Runge-Kutta 4ème ordre pour systèmes 2x2

void rk4(double& x1, double& x2, double dt, double t,
         Deriv2 f1,
         Deriv2 f2) {
    // Coefficients RK4 pour x1 et x2
    double k1_x1 = dt * f1(t, x1, x2);
    double k1_x2 = dt * f2(t, x1, x2);
    
    double k2_x1 = dt * f1(t + dt/2, x1 + k1_x1/2, x2 + k1_x2/2);
    double k2_x2 = dt * f2(t + dt/2, x1 + k1_x1/2, x2 + k1_x2/2);
    
    double k3_x1 = dt * f1(t + dt/2, x1 + k2_x1/2, x2 + k2_x2/2);
    double k3_x2 = dt * f2(t + dt/2, x1 + k2_x1/2, x2 + k2_x2/2);
    
    double k4_x1 = dt * f1(t + dt, x1 + k3_x1, x2 + k3_x2);
    double k4_x2 = dt * f2(t + dt, x1 + k3_x1, x2 + k3_x2);
    
    // Mise à jour finale
    x1 += (k1_x1 + 2*k2_x1 + 2*k3_x1 + k4_x1) / 6;
    x2 += (k1_x2 + 2*k2_x2 + 2*k3_x2 + k4_x2) / 6;
}

// Heun (Euler amélioré) pour systèmes 2x2

void heun(double& x1, double& x2, double dt, double t,
          Deriv2 f1,
          Deriv2 f2) {

    // Étape de prédiction (Euler)

    double dx1_dt = f1(t, x1, x2);
    double dx2_dt = f2(t, x1, x2);
    
    double x1_pred = x1 + dt * dx1_dt;
    double x2_pred = x2 + dt * dx2_dt;
    
    // Étape de correction (moyenne des pentes)

    double dx1_dt_pred = f1(t + dt, x1_pred, x2_pred);
    double dx2_dt_pred = f2(t + dt, x1_pred, x2_pred);
    
    // Mise à jour finale avec la moyenne
    
    x1 += dt * (dx1_dt + dx1_dt_pred) / 2;
    x2 += dt * (dx2_dt + dx2_dt_pred) / 2;
}

// Runge-Kutta 4 pour l'ordre 1
void rk4_order1(double& x, double dt, double t, Deriv1 f) {
    double k1 = dt * f(t, x);
    double k2 = dt * f(t + dt/2.0, x + k1/2.0);
    double k3 = dt * f(t + dt/2.0, x + k2/2.0);
    double k4 = dt * f(t + dt, x + k3);

    x += (k1 + 2.0*k2 + 2.0*k3 + k4) / 6.0;
}

// Heun pour l'ordre 1
void heun_order1(double& x, double dt, double t, Deriv1 f) {
    // Prédiction (Euler)
    double slope1 = f(t, x);
    double x_pred = x + dt * slope1;

    // Correction
    double slope2 = f(t + dt, x_pred);
    x += dt * (slope1 + slope2) / 2.0;
}