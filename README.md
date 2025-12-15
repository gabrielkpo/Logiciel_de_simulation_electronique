# Dashboard Simulation Circuit (Dash)

Ce projet contient un exemple de dashboard interactif en Python utilisant Plotly Dash pour visualiser les résultats d'une simulation de circuit.

Fichiers principaux:
- `app.py` : application Dash principale.
- `simulation_output.csv` : exemple de données CSV simulées (Time, InputVoltage, OutputVoltage).
- `assets/style.css` : styles CSS pour thème sombre et cartes.

Prérequis
- Python 3.8+
- pip

Installation rapide

1. Créez un environnement virtuel (recommandé) :

```bash
python -m venv .venv
source .venv/bin/activate
```

2. Installez les dépendances :

```bash
pip install dash pandas plotly numpy
```

Lancer l'application

```bash
python app.py
```

L'interface s'ouvrira par défaut sur http://127.0.0.1:8050/.

Notes d'intégration

- Le bouton "Lancer Simulation" ne lance pas réellement le code C++ ici. Il régénère des données de démonstration en fonction des paramètres saisis et les écrit dans `simulation_output.csv` pour simuler le comportement.
- Pour intégrer avec votre programme C++:
  - Remplacez la fonction `generate_simulation_csv` par un appel système à votre exécutable C++ qui produira le fichier `simulation_output.csv`.
  - Assurez-vous que l'exécutable écrit le CSV au même emplacement que `app.py` ou adaptez `CSV_PATH`.

Structure et style

Le layout respecte la disposition demandée : deux colonnes (2/3 et 1/3). La colonne gauche contient les deux graphiques empilés; la colonne droite contient le panneau de paramètres (en haut) et le tableau des données en bas. Le thème est sombre et moderne avec des cartes distinctes pour chaque section.

Limites

- Le modèle de sortie est une approximation RC simple pour visualisation. Adaptez la logique si vous avez une simulation plus précise.

Si vous voulez, j'intègre l'appel direct à votre binaire C++ et un bouton pour déclencher la simulation native (avec sécurité et gestion d'erreurs).