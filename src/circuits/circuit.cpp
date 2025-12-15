#include "circuit.hpp"
#include <iostream>
using namespace std;

// Constructeur par défaut

Circuit::Circuit() : R_(0.0), C_(0.0), L_(0.0), type_("Unknown"), frequency_(0.0), timeConstant_(0.0) {

// ici on rentre des paramètres par défauts du circuit

}

// CircuitA default constructor: prompt user for values
CircuitA::CircuitA() : Circuit() {
    cout << "--- Initialisation Circuit A (RC) ---" << endl;
    double R,C,F;
    cout << "R (Ohms) ? [1000] "; 
    if(!(cin >> R)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); R=1000.0; 
    }
    cout << "C (Farads) ? [1e-6] "; 
    if(!(cin >> C)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); C=1e-6; 
    }
    cout << "Fréquence (Hz) ? [50] "; 
    if(!(cin >> F)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); F=50.0; 
    }
    R_ = R; C_ = C; L_ = 0.0; frequency_ = F; type_ = "A"; calculerConstanteTemps();
}

// CircuitB default constructor: prompt user for R1 and R2
CircuitB::CircuitB() : Circuit() {
    cout << "--- Initialisation Circuit B (RC + diode) ---" << endl;
    double R1, R2, C, F;
    cout << "R1 (Ohms) ? [1000] "; 
    if(!(cin >> R1)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); R1=1000.0; 
    }
    cout << "R2 (Ohms) ? [1000] "; 
    if(!(cin >> R2)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); R2=1000.0; 
    }
    cout << "C (Farads) ? [1e-6] "; 
    if(!(cin >> C)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); C=1e-6; 
    }
    cout << "Fréquence (Hz) ? [50] "; 
    if(!(cin >> F)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); F=50.0; 
    }
    R_ = R1; C_ = C; L_ = 0.0; frequency_ = F; type_ = "B"; calculerConstanteTemps();
    R2_ = R2;
}

// CircuitC default constructor: prompt user
CircuitC::CircuitC() : Circuit() {
    cout << "--- Initialisation Circuit C (RLC serie) ---" << endl;
    double R,C,L,F;
    cout << "R (Ohms) ? [1000] "; 
    if(!(cin >> R)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); R=1000.0; 
    }
    cout << "C (Farads) ? [1e-6] "; 
    if(!(cin >> C)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); C=1e-6; 
    }
    cout << "L (Henrys) ? [1e-3] "; 
    if(!(cin >> L)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); L=1e-3; 
    }
    cout << "Fréquence (Hz) ? [50] "; 
    if(!(cin >> F)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); F=50.0; 
    }
    R_ = R; C_ = C; L_ = L; frequency_ = F; type_ = "C"; calculerConstanteTemps();
}

// CircuitD default constructor: prompt user
CircuitD::CircuitD() : Circuit() {
    cout << "--- Initialisation Circuit D (RLC parallele) ---" << endl;
    double R,C,L,F;
    cout << "R (Ohms) ? [1000] "; 
    if(!(cin >> R)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); R=1000.0; 
    }
    cout << "C (Farads) ? [1e-6] "; 
    if(!(cin >> C)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); C=1e-6; 
    }
    cout << "L (Henrys) ? [1e-3] "; 
    if(!(cin >> L)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); L=1e-3; 
    }
    cout << "Fréquence (Hz) ? [50] "; 
    if(!(cin >> F)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); F=50.0; 
    }
    R_ = R; C_ = C; L_ = L; frequency_ = F; type_ = "D"; calculerConstanteTemps();
}

// Constructeur param pour circuits R, C (type A)

Circuit::Circuit(double R, double C, double F) : R_(R), C_(C), L_(0.0), type_("A"), frequency_(F), timeConstant_(0.0) {
    calculerConstanteTemps();
}

// Constructeur générique R, C, L (permet B, C, D)

Circuit::Circuit(double R, double C, double L, double F) : R_(R), C_(C), L_(L), type_("C/D"), frequency_(F), timeConstant_(0.0) {
    calculerConstanteTemps();
}

// Fonction pour lire les valeurs du circuit depuis l'utilisateur

void Circuit::lireValeurs() {

    // Initialisation par défaut
    double R = 0.0, C = 0.0, L = 0.0, F = 0.0;
    string type;


    // Configuration du circuit
    cout << "=== Configuration du circuit ===" << endl;
    cout << "Résistance (Ω) ? ";
    cin >> R;
    cout << "Capacité (F) ? ";
    cin >> C;
    cout << "Inductance (H) ? ";
    cin >> L;
    cout << "Fréquence (Hz) ? ";
    cin >> F;
    cout << "Quel circuit (A/B/C/D) ? ";
    cin >> type;


    // on renvoit les valeurs lues
    cout << "-------------------------------" << endl;
    cout << "Valeurs lues :" << endl;
    cout << "  R = " << R << " Ω" << endl;
    cout << "  C = " << C << " F" << endl;
    cout << "  L = " << L << " H" << endl;
    cout << "  F = " << F << " Hz" << endl;
    cout << "  Type = " << type << endl;
    cout << "-------------------------------" << endl;
    
    // Affectation des valeurs
    R_ = R;
    C_ = C;
    L_ = L;
    // pas de D_ à stocker - la diode est traitée au niveau des dérivées (conditionnel)
    frequency_ = F;
    type_ = type;
    calculerConstanteTemps();
}

// Méthode pour calculer la constante de temps selon le type de circuit
// Faire calcul des autres constantes de temps


void Circuit::calculerConstanteTemps() {
    if (type_ == "A") {

        // Circuit RC : τ = R * C
        timeConstant_ = R_ * C_;

    } else if (type_ == "B") { 

        // faire calcul pour RCD ( pour l'instant on met pareil que RC )

        timeConstant_ = R_ * C_;
    } else if (type_ == "C" ) {

         // faire calcul pour RCD ( pour l'instant on met pareil que RC )

        timeConstant_ = R_ * C_;
    } else if (type_ == "D") {

         // faire calcul pour RCD ( pour l'instant on met pareil que RC )

        timeConstant_ = R_ * C_;
    } else {
        printf("Type de circuit inconnu pour le calcul de la constante de temps.\n");
        timeConstant_ = 0.0;
    }
}
