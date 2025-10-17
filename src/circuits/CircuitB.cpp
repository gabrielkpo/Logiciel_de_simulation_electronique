#include "circuit.hpp"
#include <cmath>
#include <iostream>
using namespace std;

// Constructeur : appelle le constructeur parent qui initialise R_, C_, frequency_, timeConstant_
CircuitB::CircuitB(double R, double C, double F) 
    : Circuit(R, C, F) {
    // Le constructeur parent a déjà initialisé tous les membres
    // Ici on peut ajouter du code spécifique à CircuitB si nécessaire
}
