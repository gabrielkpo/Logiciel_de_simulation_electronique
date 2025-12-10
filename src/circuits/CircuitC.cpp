#include "circuit.hpp"
#include <cmath>
#include <iostream>
using namespace std;

// Constructeur : appelle le constructeur parent RCLD générique (R, C, L, D=0, F)
// Le constructeur parent a initialisé R, C, L, frequency, type="C"

CircuitC::CircuitC(double R, double C, double L, double F) : Circuit(R, C, L, F) {  

    // On renvoit un message de création
    cout << "CircuitC créé : RLC série (R=" << R << "Ω, C=" << C << "F, L=" << L << "H, f=" << F << "Hz)" << endl;
}

int CircuitC::order() const { return 2; }

// Équations différentielles du circuit RLC série
void CircuitC::deriv2(double /*t*/, double vc, double vs, double ve, double &dx1, double &dx2) const {
    // vc corresponds to x1, vs to x2 in our notation
    dx1 = - (R_ / L_) * vc + (ve - vs)/(L_ * C_);
    dx2 = 0.0; // as in the simple model
}
