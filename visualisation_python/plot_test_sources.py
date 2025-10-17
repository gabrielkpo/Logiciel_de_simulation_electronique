#!/usr/bin/env python3
"""
Script Python pour visualiser les sources de tension (tests)
Charge depuis resultats/tests/ et sauvegarde les graphiques dans le même dossier
Usage: python3 plot_test_sources.py
"""

import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

# Fichier CSV des tests (chercher depuis différents emplacements)
csv_paths = [
    'resultats/tests/sources.csv',      # Si lancé depuis la racine
    '../resultats/tests/sources.csv'    # Si lancé depuis visualisation_python
]

csv_file = None
for path in csv_paths:
    if os.path.exists(path):
        csv_file = path
        break

if csv_file is None:
    print("❌ Erreur : fichier sources.csv introuvable dans resultats/tests/")
    print("   Exécutez d'abord : ./test_sources")
    sys.exit(1)

# Charger les données
print(f"📂 Chargement de {csv_file}...")
data = pd.read_csv(csv_file)
print(f"✅ {len(data)} points chargés")

# Créer une figure avec 4 sous-graphiques
fig, axes = plt.subplots(2, 2, figsize=(14, 10))
fig.suptitle('Test des Sources de Tension', fontsize=16, fontweight='bold')

# Sinus
axes[0, 0].plot(data['temps'], data['sinus'], 'b-', linewidth=2, label='Sinus')
axes[0, 0].set_title('Source Sinus (5V, 2Hz)', fontsize=12, fontweight='bold')
axes[0, 0].set_xlabel('Temps (s)')
axes[0, 0].set_ylabel('Tension (V)')
axes[0, 0].grid(True, alpha=0.3)
axes[0, 0].legend()
axes[0, 0].axhline(y=0, color='k', linestyle='-', linewidth=0.5, alpha=0.3)

# Échelon
axes[0, 1].plot(data['temps'], data['echelon'], 'r-', linewidth=2, label='Échelon')
axes[0, 1].set_title('Source Échelon (10V, t0=0.5s)', fontsize=12, fontweight='bold')
axes[0, 1].set_xlabel('Temps (s)')
axes[0, 1].set_ylabel('Tension (V)')
axes[0, 1].grid(True, alpha=0.3)
axes[0, 1].legend()
axes[0, 1].axvline(x=0.5, color='k', linestyle='--', linewidth=1, alpha=0.3, label='t0')

# Créneau
axes[1, 0].plot(data['temps'], data['creneau'], 'g-', linewidth=2, label='Créneau')
axes[1, 0].set_title('Source Créneau (3V, 1Hz, 50%)', fontsize=12, fontweight='bold')
axes[1, 0].set_xlabel('Temps (s)')
axes[1, 0].set_ylabel('Tension (V)')
axes[1, 0].grid(True, alpha=0.3)
axes[1, 0].legend()
axes[1, 0].axhline(y=0, color='k', linestyle='-', linewidth=0.5, alpha=0.3)

# Triangulaire
axes[1, 1].plot(data['temps'], data['triangle'], 'm-', linewidth=2, label='Triangulaire')
axes[1, 1].set_title('Source Triangulaire (4V, 1.5Hz)', fontsize=12, fontweight='bold')
axes[1, 1].set_xlabel('Temps (s)')
axes[1, 1].set_ylabel('Tension (V)')
axes[1, 1].grid(True, alpha=0.3)
axes[1, 1].legend()
axes[1, 1].axhline(y=0, color='k', linestyle='-', linewidth=0.5, alpha=0.3)

plt.tight_layout()

# Sauvegarder dans le dossier tests (adapter selon d'où le script est lancé)
# Déterminer le chemin de sortie basé sur le chemin du CSV trouvé
if csv_file.startswith('../'):
    # Lancé depuis visualisation_python/
    output_file = '../resultats/tests/sources_plot.png'
else:
    # Lancé depuis la racine
    output_file = 'resultats/tests/sources_plot.png'
    
plt.savefig(output_file, dpi=150, bbox_inches='tight')
print(f"✅ Figure sauvegardée : {output_file}")

# Statistiques
print("\n📊 Statistiques des sources :")
print(f"  Sinus     : min={data['sinus'].min():.2f}V, max={data['sinus'].max():.2f}V")
print(f"  Échelon   : min={data['echelon'].min():.2f}V, max={data['echelon'].max():.2f}V")
print(f"  Créneau   : min={data['creneau'].min():.2f}V, max={data['creneau'].max():.2f}V")
print(f"  Triangle  : min={data['triangle'].min():.2f}V, max={data['triangle'].max():.2f}V")

# Afficher
plt.show()
