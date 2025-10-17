#include "source.hpp"
#include <cmath>
using namespace std;  

// Constructeur par défaut

TriangulaireSource::TriangulaireSource() {
    amplitude_ = 1.0;
    frequency_ = 1.0;
    offset_ = 0.0;
}

// Constructeur paramétré

TriangulaireSource::TriangulaireSource(double amplitude, double frequency, double offset) {
    amplitude_ = amplitude;
    frequency_ = frequency;
    offset_ = offset;
}

// Calcul de la valeur : signal triangulaire

double TriangulaireSource::getValue(double t) const {
    double period = 1.0 / frequency_;
    double timeInPeriod = fmod(t, period);
    double halfPeriod = period / 2.0;

    if (timeInPeriod < halfPeriod) {
        // Montée : de offset_ à (offset_ + amplitude_)
        return offset_ + (amplitude_ / halfPeriod) * timeInPeriod;
    } else {
        // Descente : de (offset_ + amplitude_) à offset_
        return offset_ + amplitude_ - (amplitude_ / halfPeriod) * (timeInPeriod - halfPeriod);
    }
}

