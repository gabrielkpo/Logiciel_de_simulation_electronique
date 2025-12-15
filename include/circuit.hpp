#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include <string>


// On crée la classe circuit de base équipée d'un constructeur par défaut et des constructeurs paramétrés
// On définit les méthodes 
// On définit les variables 


class Circuit{
public:
    Circuit();  // Constructeur par défaut
    
    // Constructeurs spécialisés pour différents types de circuits
    Circuit(double R, double C, double F);                    // Pour circuits RC (type A)
    // Constructeur unique et générique : R, C, L (mettre L=0 si non utilisé), F
    Circuit(double R, double C, double L, double F);

    void lireValeurs();     

    // Ordre 1 par défaut
    virtual int order() const { return 1; }

    // Système 1er ordre (circuits A and B)
    virtual double deriv1(double t, double x1, double ve, double extra) const {
        (void)t; (void)x1; (void)ve; (void)extra; return 0.0;
    }

    // Système 2eme ordre (circuits C and D)
    virtual void deriv2(double t, double x1, double x2, double ve, double &dx1, double &dx2) const {
        (void)t; (void)x1; (void)x2; (void)ve; dx1 = 0.0; dx2 = 0.0;
    }

    // destructeur virtuel
    virtual ~Circuit() = default;

protected:
    double R_; // Resistance
    double C_; // Capacitance
    double L_; // Inductance (0.0 si non utilisée)
    std::string type_; // Type de circuit ( A/B )
    double frequency_; // Frequency 
    double timeConstant_; // Time constant

    // Méthodes utilitaires protégées
    void calculerConstanteTemps();
    void initialiserType();
};

// Classes dérivées pour chaque type de circuit spécifique
// Elles sont initialisées selon leur type avec les bons paramètres

class CircuitA : public Circuit {
public:
    CircuitA();
    CircuitA(double R, double C, double F);
    int order() const override;
    double deriv1(double t, double x1, double ve, double extra) const override;
};  

class CircuitB : public Circuit {
public:
    CircuitB();
        // Constructeur complet pour initialiser R1 et R2
        CircuitB(double R1, double R2, double C, double F);
    int order() const override;
    double deriv1(double t, double x1, double ve, double extra) const override;
    double getR2() const { return R2_; }
private:
    double R2_ = 1000.0;
};

class CircuitC : public Circuit {
public:
    CircuitC();
    CircuitC(double R, double C, double L, double F);
    int order() const override;
    void deriv2(double t, double x1, double x2, double ve, double &dx1, double &dx2) const override;
};  

class CircuitD : public Circuit {
public:
    CircuitD();
    CircuitD(double R, double C, double L, double F);
    int order() const override;
    void deriv2(double t, double x1, double x2, double ve, double &dx1, double &dx2) const override;
};
#endif


