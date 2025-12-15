#include "circuit.hpp"
#include <cmath>
#include <iostream>
using namespace std;

// Constructeur complet avec R1 et R2
CircuitB::CircuitB(double R1, double R2, double C, double F) : Circuit(R1, C, 0.0, F), R2_(R2) {
    cout << "CircuitB créé : R1=" << R1 << " Ω, R2=" << R2 << " Ω, C=" << C << "F, f=" << F << "Hz" << endl;
}
int CircuitB::order() const { return 1; }

// Équation différentielle du circuit RCD avec diode
double CircuitB::deriv1(double /*t*/, double vs, double ve, double extra) const {
    // extra used as R2
    double R2 = extra;
    double vBE = 0.6;
    if (ve > vBE) {
        return - (1.0/(R_ * C_) + 1.0/(R2 * C_)) * vs + (ve - vBE)/(R_ * C_);
    } else {
        return - vs/(R2 * C_);
    }
}
