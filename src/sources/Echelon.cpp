#include "source.hpp"
#include <cmath>
#include <iostream>
#include <limits>
using namespace std;  

// Constructeur par défaut

EchelonSource::EchelonSource() {
    cout << "--- Initialisation EchelonSource ---" << endl;
    double A = 5.0, t0 = 0.0, off = 0.0;
    cout << "Amplitude (V) ? [5] "; 

    if(!(cin >> A)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); A = 5.0; 
    }
    cout << "Start time (s) ? [0] "; 

    if(!(cin >> t0)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); t0 = 0.0; 
    }
    cout << "Offset (V) ? [0] "; 
    
    if(!(cin >> off)) { 
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); off = 0.0; 
    }
    amplitude_ = A; startTime_ = t0; offset_ = off;
}

// Constructeur paramétré


EchelonSource::EchelonSource(double amplitude, double startTime) {
    amplitude_ = amplitude;
    startTime_ = startTime;
}

// Calcul de la valeur : signal échelon

double EchelonSource::ve(double t) const {
    // Toutes les sources sont nulles pour t < 0
    if (t < 0.0) {
        return 0.0;
    }

    if (t < startTime_) {
        return offset_;               // Avant le début de l'échelon
    } else {
        return amplitude_ + offset_;  // Après le début de l'échelon
    }
}
