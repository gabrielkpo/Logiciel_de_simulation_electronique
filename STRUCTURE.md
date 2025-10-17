Structure du Projet 

```
be-sim/
├── main.cpp                      # Programme principal C++
├── be-sim                        # Exécutable compilé
├── CMakeLists.txt                # Configuration CMake
│
├── include/                      # Headers (.hpp)
│   └── source.hpp
│
├── src/                          # Implémentations (.cpp)
│   └── sources/
│       ├── Sinus.cpp
│       ├── Echelon.cpp
│       ├── Creneau.cpp
│       └── Triangulaire.cpp
│
├── visualisation_python/         # 🐍 Visualisation Python
│   ├── plot_sources.py           # Script Python
│   └── README.md                 # Documentation
│
├── visualisation_matlab/         # 📊 Visualisation MATLAB
│   ├── plot_sources.m            # Script MATLAB
│   └── README.md                 # Documentation
│
├── sources.csv                   # Données générées
├── sources_plot.png              # Graphiques générés
│
└── Documentation/
    ├── README.md                 # Ce fichier
    ├── README_USAGE.md           # Guide d'utilisation
    ├── VISUALISATION.md          # Guide visualisation
    └── GUIDE_VISUALISATION.md    # Guide détaillé
```
