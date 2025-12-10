#include "circuit.hpp"
#include <iostream>
using namespace std;

// Constructeur : appelle le constructeur parent générique (R, C, L, D=0, F)
// Le constructeur parent a initialisé R, C, L, frequency, type="D"

CircuitD::CircuitD(double R, double C, double L, double F): Circuit(R, C, L, F) {  

	// On renvoit un message de création
	cout << "CircuitD créé : RLC parallèle (R=" << R << "Ω, C=" << C << "F, L=" << L << "H, f=" << F << "Hz)" << endl;
}

int CircuitD::order() const { return 2; }

// Équations différentielles du circuit RLC parallèle
void CircuitD::deriv2(double /*t*/, double vc, double vs, double ve, double &dx1, double &dx2) const {
	dx1 = (ve - vc)/(R_ * C_) - vs/(L_ * C_);
	dx2 = 0.0;
}

