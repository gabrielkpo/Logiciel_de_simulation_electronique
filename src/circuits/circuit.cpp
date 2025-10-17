#include "circuit.hpp"
#include <iostream>
using namespace std;

// Constructeur par défaut
Circuit::Circuit() : R_(0.0), C_(0.0), D_(0.0), frequency_(0.0), timeConstant_(0.0) {
}

// Constructeur paramétré
Circuit::Circuit(double R, double C, double F) 
    : R_(R), C_(C), D_(0.0), frequency_(F), timeConstant_(R * C) {
}

// Fonction pour lire les valeurs du circuit depuis l'utilisateur
void Circuit::lireValeurs() {
    double R, C, F;
    string type;
    cout << "=== Configuration du circuit ===" << endl;
    cout << "Résistance (Ω) ? ";
    cin >> R;
    cout << "Capacité (F) ? ";
    cin >> C;
    cout << "Fréquence (Hz) ? ";
    cin >> F;
    cout << "Quel circuit (A/B) ? ";
    cin >> type;
    cout << "-------------------------------" << endl;
    cout << "Valeurs lues :" << endl;
    cout << "  R = " << R << " Ω" << endl;
    cout << "  C = " << C << " F" << endl;
    cout << "  F = " << F << " Hz" << endl;
    cout << "  Type = " << type << endl;
    cout << "-------------------------------" << endl;
    
    R_ = R;
    C_ = C;
    frequency_ = F;
    timeConstant_ = R * C;
    type_ = type;
}


