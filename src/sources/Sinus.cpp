#include "source.hpp"
#include <cmath>
using namespace std;  

// Constructeur par défaut

SinusSource::SinusSource() {
    amplitude_ = 1.0;
    frequency_ = 1.0;
    offset_ = 0.0;
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

