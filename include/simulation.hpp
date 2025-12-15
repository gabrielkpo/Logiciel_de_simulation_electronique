#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <string>

// On définit une classe pour gérer les paramètres de simulation
// On définit les méthodes, getters, setters ainsi que les paramètres privés


class Simulation {
public:
    // Constructeurs
    Simulation();  // Constructeur par défaut avec valeurs standard
    Simulation(int npas, double tmax);  // Constructeur paramétré
    
    // Méthode pour lire les paramètres depuis l'utilisateur
    void lireParametres();
    
    // Getters
    int getNpas() const { return npas_; }
    double getTmax() const { return tmax_; }
    double getDt() const { return dt_; }
    
    // Afficher les paramètres
    void afficherParametres() const;
    
private:
    int npas_;       // Nombre de points de simulation
    double tmax_;    // Temps maximum (secondes)
    double dt_;      // Pas de temps (calculé automatiquement)
    
    // Méthode privée pour calculer dt
    void calculerDt();
};

#endif
