#include "circuit.hpp"
#include <cmath>
#include <iostream>
using namespace std;

// Constructeur : appelle le constructeur parent générique (R, C, L=0, F)
// Le constructeur parent a initialisé R, C, frequency, L=0, type_="B"
// La diode n'est pas une résistance numérique; son effet est géré dans les équations

CircuitB::CircuitB(double R, double C, double F) : Circuit(R, C, 0.0, F) {  

    // On renvoit un message de création
    cout << "CircuitB créé : RCD (R=" << R << "Ω, C=" << C << "F, diode modeled, f=" << F << "Hz)" << endl;
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
