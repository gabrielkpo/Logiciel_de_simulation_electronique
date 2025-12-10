#!/usr/bin/env python3
"""
Script de visualisation du diagramme de Bode et de l'analyse fréquentielle
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

def plot_bode_diagram():
    """Génère le diagramme de Bode à partir des données CSV"""
    
    # Vérifier que le fichier existe
    bode_file = "../resultats/simulations/bode_diagram.csv"
    if not os.path.exists(bode_file):
        print(f"❌ Fichier {bode_file} non trouvé!")
        print("Veuillez d'abord exécuter le programme frequency_sweep")
        return
    
    # Charger les données
    df = pd.read_csv(bode_file)
    
    # Configuration de la figure
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 10))
    fig.suptitle('Diagramme de Bode - Circuit RC Passe-Bas', fontsize=16, fontweight='bold')
    
    # Couleurs pour les différentes catégories de fréquences
    colors = {'basse': 'blue', 'moyenne': 'green', 'haute': 'red'}
    
    # Graphique 1: Magnitude (dB)
    for category in ['basse', 'moyenne', 'haute']:
        mask = df['category'] == category
        if mask.any():
            ax1.semilogx(df[mask]['frequency'], df[mask]['magnitude_dB'], 
                        'o-', color=colors[category], label=f'Fréquences {category}s',
                        markersize=4, linewidth=1.5)
    
    ax1.set_xlabel('Fréquence (Hz)')
    ax1.set_ylabel('Magnitude (dB)')
    ax1.set_title('Réponse en Amplitude')
    ax1.grid(True, which="both", ls="-", alpha=0.3)
    ax1.legend()
    
    # Ligne de référence à -3dB
    ax1.axhline(y=-3, color='orange', linestyle='--', alpha=0.7, label='Fréquence de coupure (-3dB)')
    ax1.legend()
    
    # Graphique 2: Phase (degrés)
    for category in ['basse', 'moyenne', 'haute']:
        mask = df['category'] == category
        if mask.any():
            ax2.semilogx(df[mask]['frequency'], df[mask]['phase_degrees'], 
                        'o-', color=colors[category], label=f'Fréquences {category}s',
                        markersize=4, linewidth=1.5)
    
    ax2.set_xlabel('Fréquence (Hz)')
    ax2.set_ylabel('Phase (degrés)')
    ax2.set_title('Réponse en Phase')
    ax2.grid(True, which="both", ls="-", alpha=0.3)
    ax2.legend()
    
    # Lignes de référence pour la phase
    ax2.axhline(y=0, color='gray', linestyle=':', alpha=0.5)
    ax2.axhline(y=-45, color='orange', linestyle='--', alpha=0.7, label='Phase à fc (-45°)')
    ax2.axhline(y=-90, color='red', linestyle='--', alpha=0.7, label='Phase asymptotique (-90°)')
    ax2.legend()
    
    plt.tight_layout()
    
    # Sauvegarder
    output_path = "../resultats/traces/bode_diagram.png"
    plt.savefig(output_path, dpi=300, bbox_inches='tight')
    print(f"✅ Diagramme de Bode sauvegardé: {output_path}")
    
    plt.show()

def plot_comparison():
    """Compare la théorie et la simulation"""
    
    comparison_file = "../resultats/simulations/theory_vs_simulation.csv"
    if not os.path.exists(comparison_file):
        print(f"❌ Fichier {comparison_file} non trouvé!")
        return
    
    df = pd.read_csv(comparison_file)
    
    if df.empty:
        print("❌ Aucune donnée de comparaison disponible")
        return
    
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(15, 10))
    fig.suptitle('Comparaison Théorie vs Simulation', fontsize=16, fontweight='bold')
    
    # Magnitude: Théorie vs Simulation
    ax1.semilogx(df['frequency'], df['theory_mag_dB'], 'b-o', label='Théorie', markersize=6)
    ax1.semilogx(df['frequency'], df['sim_mag_dB'], 'r-s', label='Simulation', markersize=6)
    ax1.set_xlabel('Fréquence (Hz)')
    ax1.set_ylabel('Magnitude (dB)')
    ax1.set_title('Comparaison Magnitude')
    ax1.grid(True, which="both", ls="-", alpha=0.3)
    ax1.legend()
    
    # Phase: Théorie vs Simulation
    ax2.semilogx(df['frequency'], df['theory_phase'], 'b-o', label='Théorie', markersize=6)
    ax2.semilogx(df['frequency'], df['sim_phase'], 'r-s', label='Simulation', markersize=6)
    ax2.set_xlabel('Fréquence (Hz)')
    ax2.set_ylabel('Phase (degrés)')
    ax2.set_title('Comparaison Phase')
    ax2.grid(True, which="both", ls="-", alpha=0.3)
    ax2.legend()
    
    # Erreur sur la magnitude
    ax3.semilogx(df['frequency'], df['error_mag'], 'g-o', markersize=6)
    ax3.set_xlabel('Fréquence (Hz)')
    ax3.set_ylabel('Erreur Magnitude (dB)')
    ax3.set_title('Erreur sur la Magnitude')
    ax3.grid(True, which="both", ls="-", alpha=0.3)
    
    # Erreur sur la phase
    ax4.semilogx(df['frequency'], df['error_phase'], 'g-o', markersize=6)
    ax4.set_xlabel('Fréquence (Hz)')
    ax4.set_ylabel('Erreur Phase (degrés)')
    ax4.set_title('Erreur sur la Phase')
    ax4.grid(True, which="both", ls="-", alpha=0.3)
    
    plt.tight_layout()
    
    # Sauvegarder
    output_path = "../resultats/traces/theory_vs_simulation.png"
    plt.savefig(output_path, dpi=300, bbox_inches='tight')
    print(f"✅ Comparaison sauvegardée: {output_path}")
    
    plt.show()
    
    # Statistiques d'erreur
    print("\n=== Statistiques d'Erreur ===")
    print(f"Erreur moyenne magnitude: {df['error_mag'].mean():.3f} dB")
    print(f"Erreur max magnitude: {df['error_mag'].max():.3f} dB")
    print(f"Erreur moyenne phase: {df['error_phase'].mean():.3f}°")
    print(f"Erreur max phase: {df['error_phase'].max():.3f}°")

def plot_frequency_response_3d():
    """Crée une visualisation 3D du comportement fréquentiel"""
    
    bode_file = "../resultats/simulations/bode_diagram.csv"
    if not os.path.exists(bode_file):
        return
    
    df = pd.read_csv(bode_file)
    
    fig = plt.figure(figsize=(14, 8))
    
    # Graphique 3D
    ax = fig.add_subplot(121, projection='3d')
    
    # Coordonnées pour la surface 3D
    freq = df['frequency'].values
    mag = df['magnitude_dB'].values
    phase = df['phase_degrees'].values
    
    # Créer des couleurs basées sur la fréquence
    colors = plt.cm.viridis(np.log10(freq) / np.log10(freq.max()))
    
    ax.scatter(np.log10(freq), mag, phase, c=colors, s=50)
    ax.set_xlabel('log10(Fréquence)')
    ax.set_ylabel('Magnitude (dB)')
    ax.set_zlabel('Phase (°)')
    ax.set_title('Réponse 3D du Circuit')
    
    # Graphique polaire pour la phase
    ax2 = fig.add_subplot(122, projection='polar')
    
    # Convertir la phase en radians
    phase_rad = np.deg2rad(phase)
    magnitude_linear = 10**(mag/20)  # Convertir dB en linéaire
    
    ax2.plot(phase_rad, magnitude_linear, 'o-', markersize=4)
    ax2.set_title('Diagramme de Nyquist (simplifié)')
    ax2.set_xlabel('Phase')
    ax2.set_ylabel('Magnitude linéaire')
    
    plt.tight_layout()
    
    output_path = "../resultats/traces/frequency_response_3d.png"
    plt.savefig(output_path, dpi=300, bbox_inches='tight')
    print(f"✅ Visualisation 3D sauvegardée: {output_path}")
    
    plt.show()

def main():
    """Fonction principale"""
    print("🎯 Génération des graphiques d'analyse fréquentielle...")
    
    # Créer le répertoire de sortie si nécessaire
    os.makedirs("../resultats/traces", exist_ok=True)
    
    # Générer les graphiques
    plot_bode_diagram()
    #plot_comparison()
    #plot_frequency_response_3d()
    
    print("\n✅ Analyse fréquentielle terminée!")
    print("📊 Consultez les fichiers PNG dans resultats/traces/")

if __name__ == "__main__":
    main()