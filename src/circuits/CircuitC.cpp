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
void CircuitC::deriv2(double /*t*/, double vc, double i, double ve, double &dx1, double &dx2) const {
    // Sécurité : protéger contre division par 0
    if (C_ == 0.0 || L_ == 0.0) {
        dx1 = 0.0;
        dx2 = 0.0;
        return;
    }

    dx1 = i / C_;                         // dvc/dt = i / C
    dx2 = (ve - R_ * i - vc) / L_;        // di/dt = (ve - R*i - vc) / L
}
