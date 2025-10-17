#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include <string>

class Circuit{
public:
    Circuit();  // Constructeur par défaut
    Circuit(double R, double C, double F);  // Constructeur paramétré
    void lireValeurs();

protected:

    double R_; // Resistance
    double C_; // Capacitance
    double D_; // diode
    std::string type_; // Type de circuit ( A/B )
    double frequency_; // Frequency 
    double timeConstant_; // Time constant


};

class CircuitA : public Circuit {
public:
    CircuitA(double R, double C, double F);
    // Additional methods specific to CircuitA can be added here
};  

class CircuitB : public Circuit {
public:
    CircuitB(double R, double C, double F);
    // Additional methods specific to CircuitB can be added here
};

#endif

