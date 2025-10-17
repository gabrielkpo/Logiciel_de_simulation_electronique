
Scripts Python pour visualiser les sources de tension générées par le simulateur.


- Générer les données (depuis la racine du projet)


```bash
cd /Users/gabriel/be-sim
./be-sim
```

- Cela génère le fichier `sources.csv`.


Visualiser les données
```bash
cd visualisation_python
python3 plot_sources.py
```

- Résultat


Le script génère :
- **Affichage interactif** : 4 graphiques (Sinus, Échelon, Créneau, Triangulaire)
- **Fichier image** : `sources_plot.png` dans le répertoire parent
