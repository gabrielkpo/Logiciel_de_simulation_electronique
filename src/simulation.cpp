#include "simulation.hpp"
#include <iostream>
using namespace std;

// Constructeur par défaut
Simulation::Simulation() : npas_(1000), tmax_(2.0) {
    calculerDt();
}

// Constructeur paramétré
Simulation::Simulation(int npas, double tmax) : npas_(npas), tmax_(tmax) {
    calculerDt();
}

// Calcule le pas de temps
void Simulation::calculerDt() {
    dt_ = tmax_ / npas_;
}

// Lire les paramètres depuis l'utilisateur
void Simulation::lireParametres() {
    cout << "=== Configuration de la simulation ===" << endl;
    cout << "Nombre de points (npas) ? ";
    cin >> npas_;
    cout << "Temps maximum (tmax en secondes) ? ";
    cin >> tmax_;
    
    calculerDt();  // Recalculer dt après lecture
    
    cout << "-------------------------------" << endl;
    afficherParametres();
}

// Afficher les paramètres
void Simulation::afficherParametres() const {
    cout << "Paramètres de simulation :" << endl;
    cout << "  npas = " << npas_ << endl;
    cout << "  tmax = " << tmax_ << " s" << endl;
    cout << "  dt   = " << dt_ << " s" << endl;
    cout << "-------------------------------" << endl;
}
