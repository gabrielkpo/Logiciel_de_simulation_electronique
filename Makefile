# Makefile pour le simulateur de circuits électriques
CXX = g++
CXXFLAGS = -std=c++17 -I include -Wall
SRC_DIR = src
SOURCES_DIR = $(SRC_DIR)/sources
CIRCUITS_DIR = $(SRC_DIR)/circuits
TESTS_DIR = tests

# Fichiers source
SOURCES_SRC = $(wildcard $(SOURCES_DIR)/*.cpp)
CIRCUITS_SRC = $(wildcard $(CIRCUITS_DIR)/*.cpp)
COMMON_SRC = $(SRC_DIR)/simulation.cpp

# Cibles
.PHONY: all clean test_sources run_test_sources visualize_tests

all: be-sim test_sources

# Programme principal
be-sim: main.cpp $(COMMON_SRC) $(CIRCUITS_SRC) $(SOURCES_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "✅ Compilation de be-sim réussie"

# Test des sources
test_sources: $(TESTS_DIR)/test_sources.cpp $(SOURCES_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "✅ Compilation de test_sources réussie"

# Exécuter les tests des sources
run_test_sources: test_sources
	@echo "🧪 Exécution des tests des sources..."
	./test_sources

# Visualiser les résultats des tests
visualize_tests: run_test_sources
	@echo "📊 Visualisation des résultats..."
	cd visualisation_python && python3 plot_test_sources.py

# Nettoyer
clean:
	rm -f be-sim test_sources
	rm -f resultats/simulations/*.csv
	rm -f resultats/tests/*.csv resultats/tests/*.png
	rm -f resultats/traces/*.png
	@echo "🧹 Nettoyage effectué"

# Aide
help:
	@echo "Makefile pour be-sim"
	@echo ""
	@echo "Cibles disponibles :"
	@echo "  make              - Compile tout (be-sim + test_sources)"
	@echo "  make be-sim       - Compile le simulateur principal"
	@echo "  make test_sources - Compile les tests des sources"
	@echo "  make run_test_sources - Exécute les tests des sources"
	@echo "  make visualize_tests  - Teste et visualise les sources"
	@echo "  make clean        - Nettoie les fichiers compilés et résultats"
	@echo "  make help         - Affiche cette aide"
