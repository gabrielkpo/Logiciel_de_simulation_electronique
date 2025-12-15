#include "circuit.hpp"
#include <cmath>
#include <iostream>
using namespace std;

// Constructeur : appelle le constructeur parent RC (R, C, F)
// Le constructeur parent a initialisé R, C, frequency, L=0, type_="A"

CircuitA::CircuitA(double R, double C, double F) : Circuit(R, C, F) {  

    // On renvoit un message de création
    cout << "CircuitA créé : RC passe-bas (R=" << R << "Ω, C=" << C << "F, f=" << F << "Hz)" << endl;
}

int CircuitA::order() const { return 1; }

// Équation différentielle du circuit RC passe-bas : dv_s/dt = (ve - v_s) / (R*C)
double CircuitA::deriv1(double /*t*/, double vs, double ve, double /*extra*/) const {
    return (ve - vs) / (R_ * C_);
}
