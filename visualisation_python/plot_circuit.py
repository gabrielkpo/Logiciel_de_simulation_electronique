#!/usr/bin/env python3
"""
Script Python pour visualiser la sortie du circuit RC
Nécessite: pip3 install matplotlib pandas
Usage: python3 plot_circuit.py
"""

import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

# Chercher le fichier CSV
csv_file = None
search_paths = [
    '../resultats/simulations/circuit_output.csv',
    '../circuit_output.csv',
    'circuit_output.csv'
]

for path in search_paths:
    if os.path.exists(path):
        csv_file = path
        break

if csv_file is None:
    print("❌ Erreur : fichier circuit_output.csv introuvable.")
    print("   Exécutez d'abord : ./be-sim")
    sys.exit(1)

# Charger les données
print(f"📂 Chargement de {csv_file}...")
data = pd.read_csv(csv_file)
print(f"✅ {len(data)} points chargés")

# Créer la figure
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 8))

# Graphique 1 : Entrée et sortie
ax1.plot(data['temps'], data['Vin'], 'b-', linewidth=2, label='Vin (entrée)', alpha=0.7)
ax1.plot(data['temps'], data['Vout'], 'r-', linewidth=2, label='Vout (sortie)')
ax1.set_title('Circuit RC - Entrée et Sortie', fontsize=14, fontweight='bold')
ax1.set_xlabel('Temps (s)')
ax1.set_ylabel('Tension (V)')
ax1.grid(True, alpha=0.3)
ax1.legend(loc='upper right')

# Graphique 2 : Différence (erreur de suivi)
difference = data['Vin'] - data['Vout']
ax2.plot(data['temps'], difference, 'g-', linewidth=2, label='Vin - Vout')
ax2.axhline(y=0, color='k', linestyle='--', linewidth=1, alpha=0.5)
ax2.set_title('Erreur de suivi', fontsize=14, fontweight='bold')
ax2.set_xlabel('Temps (s)')
ax2.set_ylabel('Différence (V)')
ax2.grid(True, alpha=0.3)
ax2.legend(loc='upper right')

plt.tight_layout()

# Sauvegarder
output_file = '../resultats/traces/circuit_output_plot.png'
plt.savefig(output_file, dpi=150, bbox_inches='tight')
print(f"✅ Figure sauvegardée : {output_file}")

# Afficher
plt.show()
