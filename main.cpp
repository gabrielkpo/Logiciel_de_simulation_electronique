#include <iostream>
#include <fstream>
#include <memory>
#include "source.hpp"
#include "circuit.hpp"
#include "simulation.hpp"

using namespace std;

int main() {
    cout << "=== Simulateur de Circuits Électriques ===" << endl;
    
    // Créer le circuit et la source d'entrée
    CircuitA circuit(1000, 1e-6, 50);           // R=1kΩ, C=1µF, F=50Hz
    SinusSource source(5.0, 50.0, 0.0);         // 5V, 50Hz
    
    // Créer la simulation avec paramètres par défaut (ou demander à l'utilisateur)
    Simulation sim(1000, 1.0);  // 1000 points, 2 secondes
    // Ou bien : Simulation sim; sim.lireParametres();
    
    sim.afficherParametres();
    
    // État initial du circuit (tension aux bornes du condensateur)
    double Vc = 0.0;
    
    // Générer fichier CSV pour la sortie du circuit
    ofstream fichier("resultats/simulations/circuit_output.csv");
    fichier << "temps,Vin,Vout" << endl;
    
    for(int i = 0; i <= sim.getNpas(); i++) {
        double t = i * sim.getDt();
        double Vin = source.getValue(t);
        
        // Calcul avec méthode d'Euler : dVc/dt = (Vin - Vc) / (R*C)
        double tau = 1000 * 1e-6;  // R * C = constante de temps
        double dVc = (Vin - Vc) / tau * sim.getDt();
        Vc += dVc;
        
        fichier << t << "," << Vin << "," << Vc << endl;
    }
    
    fichier.close();
    cout << "✅ Fichier 'resultats/simulations/circuit_output.csv' généré avec succès !" << endl;
    cout << "   " << (sim.getNpas()+1) << " points de 0 à " << sim.getTmax() << " secondes" << endl;
    
    return 0;
}