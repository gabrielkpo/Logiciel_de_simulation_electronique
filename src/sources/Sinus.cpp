#include "source.hpp"
#include <cmath>
#include <iostream>
#include <limits>
using namespace std;  

// Constructeur par défaut
SinusSource::SinusSource() {
    std::cout << "--- Initialisation SinusSource ---" << std::endl;
    double A=5.0, f=50.0, off=0.0;
    std::cout << "Amplitude (V) ? [5] "; if(!(std::cin >> A)) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); A=5.0; }
    std::cout << "Fréquence (Hz) ? [50] "; if(!(std::cin >> f)) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); f=50.0; }
    std::cout << "Offset (V) ? [0] "; if(!(std::cin >> off)) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); off=0.0; }
    amplitude_ = A;
    frequency_ = f;
    offset_ = off;
}

// Constructeur paramétré

SinusSource::SinusSource(double amplitude, double frequency, double offset) {
    amplitude_ = amplitude;
    frequency_ = frequency;
    offset_ = offset;
}

// Calcul de la valeur : signal sinusoïdal

double SinusSource::getValue(double t) const {
    return amplitude_ * sin(2 * M_PI * frequency_ * t) + offset_;
}

