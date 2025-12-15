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
// Convention d'état : x1 = vc (tension sur le condensateur), x2 = i (courant dans l'inductance)
// Topologie : source ve -> inductance L -> noeud (R en parallèle avec C vers la masse)
// dvc/dt = (1/C) * ( i - vc/R )
// di/dt  = (1/L) * ( ve - vc )
void CircuitD::deriv2(double /*t*/, double vc, double i, double ve, double &dx1, double &dx2) const {
	if (C_ == 0.0 || L_ == 0.0 || R_ == 0.0) {
		dx1 = 0.0;
		dx2 = 0.0;
		return;
	}

	dx1 = (i - vc / R_) / C_;   // dvc/dt
	dx2 = (ve - vc) / L_;       // di/dt
}

