#include "source.hpp"
#include <cmath>
using namespace std;  

// Constructeur par défaut

CreneauSource::CreneauSource() {
    amplitude_ = 1.0;
    frequency_ = 1.0;
    dutyCycle_ = 0.5;
    offset_ = 0.0;
}

// Constructeur paramétré

CreneauSource::CreneauSource(double amplitude, double frequency, double dutyCycle, double offset) {
    amplitude_ = amplitude;
    frequency_ = frequency;  // ← AJOUTÉ
    dutyCycle_ = dutyCycle;  // ← AJOUTÉ
    offset_ = offset;
}

// Calcul de la valeur : signal carré/créneau

double CreneauSource::getValue(double t) const {
    double period = 1.0 / frequency_;
    double timeInPeriod = fmod(t, period);  // modulo fonctionne avec les doubles
    double onTime = period * dutyCycle_;
    
    if ( timeInPeriod < onTime ) {
        return amplitude_ + offset_;             // Dans la partie haute
    } else {
        return offset_;                          // Dans la partie basse
    }
}

