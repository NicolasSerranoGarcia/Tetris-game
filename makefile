# Compilador y opciones
CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++17 $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)

# Nombre del ejecutable final
TARGET = tetris

# Directorios
SRC_DIR = .
SCREEN_DIR = Screen
OBJ_DIR = obj

# Archivos fuente
SRC = $(SRC_DIR)/main.cc $(SCREEN_DIR)/Screen.cc

# Archivos objeto
OBJ = $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(filter $(SRC_DIR)/%,$(SRC))) \
      $(patsubst $(SCREEN_DIR)/%.cc,$(OBJ_DIR)/$(SCREEN_DIR)/%.o,$(filter $(SCREEN_DIR)/%,$(SRC)))

# Regla principal
all: $(OBJ_DIR) $(TARGET)

# Crear directorios necesarios
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/$(SCREEN_DIR)

# Enlazar todos los objetos
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compilar main.cc
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cc $(SCREEN_DIR)/Screen.h
	$(CXX) $(CXXFLAGS) -I$(SCREEN_DIR) -c $< -o $@

# Compilar Screen/Screen.cc
$(OBJ_DIR)/$(SCREEN_DIR)/Screen.o: $(SCREEN_DIR)/Screen.cc $(SCREEN_DIR)/Screen.h
	$(CXX) $(CXXFLAGS) -I$(SCREEN_DIR) -c $< -o $@

# Limpiar
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean