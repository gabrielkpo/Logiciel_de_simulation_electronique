
Script MATLAB pour visualiser les sources de tension générées par le simulateur.

## Utilisation

- Générer les données (depuis la racine du projet)


```bash
cd /Users/gabriel/be-sim
./be-sim
```

Cela génère le fichier `sources.csv`.


- Visualiser dans MATLAB


**Option A : Interface MATLAB**
```matlab
cd visualisation_matlab
run('plot_sources.m')
```

**Option B : Ligne de commande**
```bash
cd /Users/gabriel/be-sim/visualisation_matlab
matlab -nodisplay -r "run('plot_sources.m'); exit"
```


- Résultat


Le script génère :
**Figure interactive** : 4 sous-graphiques (Sinus, Échelon, Créneau, Triangulaire)
**Fichier image** : `sources_plot.png` dans le répertoire parent
