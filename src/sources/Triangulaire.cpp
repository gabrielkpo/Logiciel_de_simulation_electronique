#include "source.hpp"
#include <cmath>
#include <iostream>
#include <limits>
using namespace std;  

// Constructeur par défaut
TriangulaireSource::TriangulaireSource() {
    std::cout << "--- Initialisation TriangulaireSource ---" << std::endl;
    double A=5.0, f=50.0, off=0.0;
    std::cout << "Amplitude (V) ? [5] "; 
    if(!(std::cin >> A)) { 
        std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); A=5.0; 
    }
    
    std::cout << "Fréquence (Hz) ? [50] "; 
    if(!(std::cin >> f)) { 
        std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); f=50.0; 
    }

    std::cout << "Offset (V) ? [0] "; 
    if(!(std::cin >> off)) { 
        std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); off=0.0; 
    }

    amplitude_ = A;
    frequency_ = f;
    offset_ = off;
}

// Constructeur paramétré

TriangulaireSource::TriangulaireSource(double amplitude, double frequency, double offset) {
    amplitude_ = amplitude;
    frequency_ = frequency;
    offset_ = offset;
}

// Calcul de la valeur : signal triangulaire

double TriangulaireSource::ve(double t) const {
    // Null for negative time per specification
    if (t < 0.0) {
        return 0.0;
    }

    double period = 1.0 / frequency_;
    double timeInPeriod = fmod(t, period);
    if (timeInPeriod < 0.0) timeInPeriod += period;
    double halfPeriod = period / 2.0;

    if (timeInPeriod < halfPeriod) {
        // Montée : de offset_ à (offset_ + amplitude_)
        return offset_ + (amplitude_ / halfPeriod) * timeInPeriod;
    } else {
        // Descente : de (offset_ + amplitude_) à offset_
        return offset_ + amplitude_ - (amplitude_ / halfPeriod) * (timeInPeriod - halfPeriod);
    }
}

