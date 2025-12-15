#include "source.hpp"
#include <cmath>
#include <iostream>
#include <limits>
using namespace std;  

// Constructeur par défaut

RectangulaireSource::RectangulaireSource() {
    cout << "--- Initialisation RectangulaireSource ---" << endl;
    double A = 5.0, f = 1.0, duty = 0.5, off = 0.0;
    cout << "Amplitude (V) ? [5] "; 
    if(!(cin >> A)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); A = 5.0; 
    }

    cout << "Fréquence (Hz) ? [1] "; 
    if(!(cin >> f)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); f = 1.0; 
    }

    cout << "Duty cycle (0-1) ? [0.5] "; 
    if(!(cin >> duty)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); duty = 0.5; 
    }

    cout << "Offset (V) ? [0] "; 
    if(!(cin >> off)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); off = 0.0; 
    }
    
    amplitude_ = A; frequency_ = f; dutyCycle_ = duty; offset_ = off;
}

// Constructeur paramétré

RectangulaireSource::RectangulaireSource(double amplitude, double frequency, double dutyCycle, double offset) {
    amplitude_ = amplitude;
    frequency_ = frequency;
    dutyCycle_ = dutyCycle;
    offset_ = offset;
}

// Calcul de la valeur : signal rectangulaire

double RectangulaireSource::ve(double t) const {
    // 1) Null for negative time
    if (t < 0.0) {
        return 0.0;
    }

    double period = 1.0 / frequency_;
    double timeInPeriod = fmod(t, period);  // modulo fonctionne avec les doubles
    if (timeInPeriod < 0.0) timeInPeriod += period;
    double onTime = period * dutyCycle_;
    
    if ( timeInPeriod < onTime ) {
        return amplitude_ + offset_;             // Dans la partie haute
    } else {
        return offset_;                          // Dans la partie basse
    }
}

