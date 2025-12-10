#include <iostream>
#include <memory>
#include <limits>
#include "source.hpp"

using namespace std;

// Initialise et retourne une source configurée par l'utilisateur.
// useDefaults = true -> on retourne une SinusSource avec valeurs par défaut.
unique_ptr<Source> initialiserSource(bool useDefaults, double &A, double &f, double &off) {
    // valeurs par défaut
    A = 5.0;
    f = 50.0;
    off = 0.0;

    if (useDefaults) {
        return make_unique<SinusSource>(A, f, off);
    }

    cout << "Choisir le type de source:" << endl;
    cout << "  1 - Sinus (A, f, offset)" << endl;
    cout << "  2 - Echelon (amplitude, startTime)" << endl;
    cout << "  3 - Triangulaire (A, f, offset)" << endl;
    cout << "  4 - Creneau (A, f, dutyCycle, offset)" << endl;
    cout << "  5 - Rectangulaire (A, f, dutyCycle, offset)" << endl;
    int choixSource = 1;
    if (!(cin >> choixSource)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choixSource = 1;
    }

    switch (choixSource) {
        case 1: {
            cout << "Amplitude de la source (V) ? [5] "; if(!(cin >> A)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); A=5.0; }
            cout << "Fréquence de la source (Hz) ? [50] "; if(!(cin >> f)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); f=50.0; }
            cout << "Offset (V) ? [0] "; if(!(cin >> off)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); off=0.0; }
            return make_unique<SinusSource>(A, f, off);
        }
        case 2: {
            double amp = 1.0, t0 = 0.0;
            cout << "Amplitude de l'echelon (V) ? [1] "; if(!(cin >> amp)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); amp=1.0; }
            cout << "Temps de début (s) ? [0] "; if(!(cin >> t0)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); t0=0.0; }
            return make_unique<EchelonSource>(amp, t0);
        }
        case 3: {
            cout << "Amplitude (V) ? [5] "; if(!(cin >> A)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); A=5.0; }
            cout << "Fréquence (Hz) ? [50] "; if(!(cin >> f)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); f=50.0; }
            cout << "Offset (V) ? [0] "; if(!(cin >> off)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); off=0.0; }
            return make_unique<TriangulaireSource>(A, f, off);
        }
        case 4: {
            double duty = 0.5;
            cout << "Amplitude (V) ? [5] "; if(!(cin >> A)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); A=5.0; }
            cout << "Fréquence (Hz) ? [50] "; if(!(cin >> f)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); f=50.0; }
            cout << "Duty cycle (0-1) ? [0.5] "; if(!(cin >> duty)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); duty=0.5; }
            cout << "Offset (V) ? [0] "; if(!(cin >> off)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); off=0.0; }
            return make_unique<CreneauSource>(A, f, duty, off);
        }
        case 5: {
            double duty = 0.5;
            cout << "Amplitude (V) ? [5] "; if(!(cin >> A)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); A=5.0; }
            cout << "Fréquence (Hz) ? [50] "; if(!(cin >> f)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); f=50.0; }
            cout << "Duty cycle (0-1) ? [0.5] "; if(!(cin >> duty)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); duty=0.5; }
            cout << "Offset (V) ? [0] "; if(!(cin >> off)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); off=0.0; }
            return make_unique<RectangulaireSource>(A, f, duty, off);
        }
        default:
            cout << "Choix invalide, on prend Sinus par défaut." << endl;
            return make_unique<SinusSource>(A, f, off);
    }
}
