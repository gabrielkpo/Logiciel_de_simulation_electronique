#include <iostream>
#include <fstream>
#include <memory>
#include "source.hpp"

using namespace std;

/**
 * Programme de test pour valider les sources de tension
 * Génère les fichiers dans resultats/tests/
 */
int main() {
    cout << "=== Test des Sources de Tension ===" << endl;
    
    // Créer les sources avec des paramètres de test
    SinusSource sinus(5.0, 2.0, 0.0);           // 5V, 2Hz
    EchelonSource echelon(10.0, 0.5);           // 10V, début à 0.5s
    CreneauSource creneau(3.0, 1.0, 0.5, 0.0);  // 3V, 1Hz, 50% duty
    TriangulaireSource triangle(4.0, 1.5, 0.0); // 4V, 1.5Hz
    
    // Paramètres de simulation
    int npas = 1000;        // Nombre de points
    double tmax = 2.0;      // Temps maximum (secondes)
    double dt = tmax / npas;
    
    // Générer fichier CSV pour TOUTES les sources dans le dossier tests
    ofstream fichier("resultats/tests/sources.csv");
    fichier << "temps,sinus,echelon,creneau,triangle" << endl;
    
    for(int i = 0; i <= npas; i++) {
        double t = i * dt;
        fichier << t << ","
                << sinus.getValue(t) << ","
                << echelon.getValue(t) << ","
                << creneau.getValue(t) << ","
                << triangle.getValue(t) << endl;
    }
    
    fichier.close();
    cout << "✅ Fichier 'resultats/tests/sources.csv' généré avec succès !" << endl;
    cout << "   " << (npas+1) << " points de 0 à " << tmax << " secondes" << endl;
    cout << endl;
    cout << "💡 Pour visualiser : cd visualisation_python && python3 plot_test_sources.py" << endl;
    
    return 0;
}
