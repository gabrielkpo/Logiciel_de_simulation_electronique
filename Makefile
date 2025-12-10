## Makefile pour le simulateur de circuits électriques

# Compilateur et flags
CXX       = g++
CXXFLAGS  = -std=c++17 -I include -Wall

# Répertoires
SRC_DIR       = src
SOURCES_DIR   = $(SRC_DIR)/sources
CIRCUITS_DIR  = $(SRC_DIR)/circuits
TESTS_DIR     = tests
VIZ_DIR       = visualisation_python
RESULTS_SIM   = resultats/simulations
RESULTS_TESTS = resultats/tests
RESULTS_TRACES= resultats/traces

# Exécutables externes
PY = python3

# Fichiers source
SOURCES_SRC  = $(wildcard $(SOURCES_DIR)/*.cpp)
CIRCUITS_SRC = $(wildcard $(CIRCUITS_DIR)/*.cpp)
COMMON_SRC   = $(SRC_DIR)/simulation.cpp $(SRC_DIR)/solver.cpp $(SRC_DIR)/initialisation.cpp $(SRC_DIR)/sim_context.cpp
CORE_SRC     = $(COMMON_SRC) $(CIRCUITS_SRC) $(SOURCES_SRC)

# Scripts Python
PLOT_CIRCUIT       = plot_circuit.py
PLOT_TEST_SOURCES  = plot_test_sources.py
PLOT_FREQUENCY     = plot_frequency_analysis.py

# Cibles
.PHONY: all clean test_sources run_test_sources test_balayage_frequence run_test_balayage visualize_tests simulate plot_circuit simplot bode re help

BINARIES = be-sim test_sources test_balayage_frequence

all: $(BINARIES)

# Programme principal
be-sim: main.cpp $(CORE_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "✅ Compilation de be-sim réussie"

# Test des sources
test_sources: $(TESTS_DIR)/test_sources.cpp $(SOURCES_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "✅ Compilation de test_sources réussie"

# Test du balayage en fréquence
test_balayage_frequence: $(TESTS_DIR)/test_balayage_frequence.cpp $(CORE_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "✅ Compilation de test_balayage_frequence réussie"

# Exécuter les tests des sources
run_test_sources: test_sources
	@echo "🧪 Exécution des tests des sources..."
	./test_sources

# Exécuter le test du balayage en fréquence
run_test_balayage: test_balayage_frequence
	@echo "🔍 Exécution du test de balayage en fréquence..."
	./test_balayage_frequence

# Visualiser les résultats des tests
visualize_tests: run_test_sources
	@echo "📊 Visualisation des résultats..."
	cd $(VIZ_DIR) && $(PY) $(PLOT_TEST_SOURCES)

# Exécuter la simulation principale
simulate: be-sim
	@echo "▶️  Exécution de la simulation..."
	./be-sim

# Générer le graphique principal de la simulation
plot_circuit:
	@echo "📈 Génération du graphique..."
	cd $(VIZ_DIR) && $(PY) $(PLOT_CIRCUIT)

# Tout-en-un : compiler (si nécessaire), exécuter la simulation et tracer
simplot: simulate plot_circuit
	@echo "✅ Simulation + visualisation terminées"

# Analyser la réponse en fréquence et générer le diagramme de Bode
bode: test_balayage_frequence
	@echo "🔍 Analyse fréquentielle en cours..."
	./test_balayage_frequence
	@echo "📊 Génération des diagrammes de Bode..."
	cd $(VIZ_DIR) && $(PY) $(PLOT_FREQUENCY)

# Nettoyer
clean:
	rm -f be-sim test_sources test_balayage_frequence
	rm -f $(RESULTS_SIM)/*.csv
	rm -f $(RESULTS_TESTS)/*.csv $(RESULTS_TESTS)/*.png
	rm -f $(RESULTS_TRACES)/*.png
	@echo "🧹 Nettoyage effectué"

# Rebuild complet
re: clean all

# Aide
help:
	@echo "Makefile pour be-sim"
	@echo ""
	@echo "Cibles disponibles :"
	@echo "  make / make all         - Compile tout ($(BINARIES))"
	@echo "  make be-sim             - Compile le simulateur principal"
	@echo "  make simulate           - Exécute ./be-sim"
	@echo "  make plot_circuit       - Trace le graphique principal"
	@echo "  make simplot            - Compile (si besoin), exécute et trace"
	@echo "  make bode               - Analyse fréquentielle + diagramme de Bode"
	@echo "  make test_sources       - Compile les tests des sources"
	@echo "  make run_test_sources   - Exécute les tests des sources"
	@echo "  make test_balayage_frequence - Compile le test de balayage en fréquence"
	@echo "  make run_test_balayage  - Exécute le test de balayage en fréquence"
	@echo "  make visualize_tests    - Visualise les résultats des tests"
	@echo "  make clean              - Nettoie les binaires et résultats"
	@echo "  make re                 - Clean + all"
	@echo "  make help               - Affiche cette aide"
