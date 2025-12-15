#include "circuit.hpp"
#include "sim_context.hpp"
#include "simulation.hpp"
#include "solver.hpp"
#include "source.hpp"
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits> // pour numeric_limits utilisé lors de la lecture utilisateur
#include <memory>

// déclaration fonction initialisation source
std::unique_ptr<Source> initialiserSource(bool useDefaults, double &A,
                                          double &f, double &off);

using namespace std;

// ==========================
// Programme principal (CLI)
// - Choix du mode (simulation / test)

// - Si simulation:
// - Choix du circuit (A/B/C/D)
// - Appel fonction lecture des paramètres de simulation (npas, tmax)
// - Choix type de source et variables associées
// - Choix de la méthode numérique (Euler / Euler 2x2 / RK4 / Heun)
// - Boucle de simulation -> écriture CSV (temps, Vin, Vout)

// - Si test:
// - Choix du circuit
// - Choix de la source
// -
// ==========================

int main() {

  cout << "=== Simulateur de Circuits Électriques ===" << endl;

  // Utiliser les paramètres par défaut ou entrer des paramètres ?
  cout << "Utiliser les paramètres par défaut pour la simulation ? (y/N) ";
  char useDefChar;
  cin >> useDefChar;
  bool useDefaults = (useDefChar == 'y' || useDefChar == 'Y');

  // Choix du circuit
  char choixCircuit = 'A';
  if (!useDefaults) {
    cout << "Choisir le type de circuit:" << endl;
    cout << "  A - RC (passe-bas)" << endl;
    cout << "  B - RC avec diode" << endl;
    cout << "  C - RLC série" << endl;
    cout << "  D - RLC parallèle" << endl;
    cin >> choixCircuit;
  } else {
    cout << "Utilisation des paramètres par défaut (Circuit A, méthode Euler, "
            "R=1000, C=1e-6, etc.)"
         << endl;
  }

  // Paramètres de simulation
  Simulation sim;
  if (!useDefaults) {
    sim.lireParametres();
  } else {
    // garder les valeurs par défaut du constructeur Simulation()
  }

  // Déclaration des paramètres du circuit (valeurs par défaut)
  double R = 1000.0, C = 1e-6, L = 1e-3;
  double R2 = 1000.0;

  // Choix et création de la source
  double A = 5.0, f = 50.0, off = 0.0;

  // Appel à la fonction d'initialisation des sources
  unique_ptr<Source> source = initialiserSource(useDefaults, A, f, off);

  // Choix et stockage de la méthode de résolution
  // initialisation à 1 par défaut
  int choixMeth = 1;
  if (!useDefaults) {
    cout << "Choisir la méthode de résolution:" << endl;
    cout << "  1 - Euler (1er ordre)" << endl;
    cout << "  2 - Euler (système 2x2)" << endl;
    cout << "  3 - Runge-Kutta 4 (2x2)" << endl;
    cout << "  4 - Heun (2x2)" << endl;
    cin >> choixMeth;
  }

  // Si on utilise les paramètres par défaut, afficher un résumé compact
  if (useDefaults) {
    cout << "Paramètres par défaut utilisés :" << endl;
    cout << "  Circuit = " << choixCircuit << " (A=RC passe-bas)" << endl;
    cout << "  Méthode = " << choixMeth << " (1=Euler)" << endl;
    cout << "  Simulation : npas=" << sim.getNpas()
         << ", tmax=" << sim.getTmax() << ", dt=" << sim.getDt() << endl;
    cout << "  Source (par défaut) : Sinus A=" << A << " V, f=" << f
         << " Hz, offset=" << off << " V" << endl;
    cout << "  Circuit params : R=" << R << " Ω, C=" << C << " F, L=" << L
         << " H, R2=" << R2 << " Ω" << endl;
  }

  // Lecture des paramètres du circuit ? a revoir

  // Si l'utilisateur choisit B, on demande R1 (R1_) et R2 (R2_) séparément
  // On affecte R1
  // problème , on affecte pas R2
  // problème on affaitre pas R1 et R2 si useDefaults
  // On demande C
  // On affecte C

  if (!useDefaults) {

    if (choixCircuit == 'B') {
      double R1 = 1000.0;
      cout << "R1 (Ohms) ? [1000] ";
      if (!(cin >> R1)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        R1 = 1000.0;
      }
      cout << "R2 (Ohms) ? [1000] ";
      if (!(cin >> R2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        R2 = 1000.0;
      }
      R = R1;
      cout << "C (Farads) ? [1e-6] ";
      if (!(cin >> C)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        C = 1e-6;
      }

    } else {
      cout << "R (Ohms) ? [1000] ";
      if (!(cin >> R)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        R = 1000.0;
      }
      cout << "C (Farads) ? [1e-6] ";
      if (!(cin >> C)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        C = 1e-6;
      }

      if (choixCircuit == 'C' || choixCircuit == 'D') {
        cout << "L (Henrys) ? [1e-3] ";
        if (!(cin >> L)) {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          L = 1e-3;
        }
      }
    }
  } else {
    // valeurs par défaut déjà affectées
  }

  // Instanciation du circuit

  // On utilise un pointeur intelligent
  unique_ptr<Circuit> circuitPtr;

  switch (choixCircuit) {
  case 'A':
    circuitPtr = make_unique<CircuitA>(R, C, f);
    break;
  case 'B':
    circuitPtr = make_unique<CircuitB>(R, R2, C, f);
    break;
  case 'C':
    circuitPtr = make_unique<CircuitC>(R, C, L, f);
    break;
  case 'D':
    circuitPtr = make_unique<CircuitD>(R, C, L, f);
    break;
  default:
    cout << "Choix invalide, défaut A" << endl;
    circuitPtr = make_unique<CircuitA>(R, C, f);
    break;
  }

  // États initiaux des variables d'état et wrappers
  // Ces éléments sont fournis par la structure SimContext, extraite en module
  SimContext ctx = createSimContext(*circuitPtr, *source, R2);

  // Génération du fichier CSV pour tracer Vout(t)
  // Crée le dossier de sortie si nécessaire
  std::filesystem::create_directories("resultats/simulations");
  ofstream fichier("resultats/simulations/circuit_output.csv");
  fichier << "temps,Vin,Vout" << endl;

  // Boucle de simulation

  for (int i = 0; i <= sim.getNpas(); ++i) {

    // Calcul de l'entrée ve(t) à l'instant courant
    double t = i * sim.getDt();
    double Vin = source->ve(t);

    // On applique la méthode numérique choisie suivant le type d'ordre du
    // circuit
    if (circuitPtr->order() == 1) {

      // 1er ordre : appliquer la méthode choisie
      if (choixMeth == 3) {
        rk4_order1(ctx.x1, sim.getDt(), t, ctx.f1);
      } else if (choixMeth == 4) {
        heun_order1(ctx.x1, sim.getDt(), t, ctx.f1);
      } else {
        // Défaut ou choix 1 (Euler) ou 2 (Euler 2x2 pas applicable)
        euler1(ctx.x1, sim.getDt(), t, ctx.f1);
      }
    } else {

      // 2ème ordre : utiliser les wrappers f2_1 / f2_2 et
      // Différents cas en fonction de la méthode choisie choixMeth

      if (choixMeth == 2) {
        euler2(ctx.x1, ctx.x2, sim.getDt(), t, ctx.f2_1, ctx.f2_2);

      } else if (choixMeth == 3) {
        rk4(ctx.x1, ctx.x2, sim.getDt(), t, ctx.f2_1, ctx.f2_2);

      } else if (choixMeth == 4) {
        heun(ctx.x1, ctx.x2, sim.getDt(), t, ctx.f2_1, ctx.f2_2);

      } else {
        // défaut: RK4
        rk4(ctx.x1, ctx.x2, sim.getDt(), t, ctx.f2_1, ctx.f2_2);
      }
    }

    // pour avoir des sorties propres (éviter les -0.000000)

    if (fabs(ctx.x1) < 1e-12)
      ctx.x1 = 0.0;
    if (fabs(ctx.x2) < 1e-12)
      ctx.x2 = 0.0;

    // Tableau de sortie tension observée Vout = x1
    fichier << t << "," << Vin << "," << ctx.x1 << endl;
  }

  fichier.close();

  // Message de succès et rappel des paramètres
  // Affichage pas et temps de simulation

  cout << " Fichier 'resultats/simulations/circuit_output.csv' généré avec "
          "succès !"
       << endl;
  cout << "   " << (sim.getNpas() + 1) << " points de 0 à " << sim.getTmax()
       << " secondes" << endl;
  return 0;
}