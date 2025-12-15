#include "source.hpp"
#include <cmath>
#include <iostream>
#include <limits>
using namespace std;  

// Constructeur par défaut pour les test
CreneauSource::CreneauSource() {
    std::cout << "--- Initialisation CreneauSource ---" << std::endl;
    double A=5.0, f=50.0, duty=0.5, off=0.0;
    std::cout << "Amplitude (V) ? [5] "; 

    if(!(std::cin >> A)) { 
        std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); A=5.0; 
    }
    std::cout << "Fréquence (Hz) ? [50] "; 

    if(!(std::cin >> f)) { 
        std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); f=50.0; 
    }
    std::cout << "Duty cycle (0-1) ? [0.5] "; 

    if(!(std::cin >> duty)) { 
        std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); duty=0.5; 
    }
    std::cout << "Offset (V) ? [0] "; 
    
    if(!(std::cin >> off)) { 
        std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); off=0.0; 
    }
    amplitude_ = A; frequency_ = f; dutyCycle_ = duty; offset_ = off;
}

// Constructeur paramétré 

CreneauSource::CreneauSource(double amplitude, double frequency, double dutyCycle, double offset) {
    amplitude_ = amplitude;
    frequency_ = frequency;  // ← AJOUTÉ
    dutyCycle_ = dutyCycle;  // ← AJOUTÉ
    offset_ = offset;
}

// Calcul de la valeur : signal carré/créneau
// Remplacé : getValue -> ve ; ajout de la condition t < 0
double CreneauSource::ve(double t) const {
    // 1) Toutes les sources sont nulles pour t < 0
    if (t < 0.0) {
        return 0.0;
    }

    // 2) Calcul du créneau pour t >= 0
    double period = 1.0 / frequency_;
    double timeInPeriod = fmod(t, period);  // modulo pour doubles
    if (timeInPeriod < 0.0) {
        timeInPeriod += period; // sécurise pour valeurs négatives éventuelles
    }
    double onTime = period * dutyCycle_;

    if (timeInPeriod < onTime) {
        return amplitude_ + offset_; // partie haute
    } else {
        return offset_;              // partie basse
    }
}

