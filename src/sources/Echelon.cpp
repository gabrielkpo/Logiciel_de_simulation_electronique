#include "source.hpp"
#include <cmath>
using namespace std;  

// Constructeur par défaut

EchelonSource::EchelonSource() {
    amplitude_ = 1.0;
    startTime_ = 0.0;
    offset_ = 0.0;
}

// Constructeur paramétré

EchelonSource::EchelonSource(double amplitude, double startTime) {
    amplitude_ = amplitude;
    startTime_ = startTime;
}

// Calcul de la valeur : signal échelon

double EchelonSource::getValue(double t) const {

    if ( t < startTime_ ) {
        return offset_;               // Avant le début de l'échelon
    } else {
        return amplitude_ + offset_;  // Après le début de l'échelon
    }

}
