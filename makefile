# Makefile para proyecto Tetris con soporte multi-directorio
CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++17 $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf
TARGET = tetris

# Configuración de directorios
SRC_DIR = .
CLASS_DIRS = Screen Font Button # Añade aquí tus carpetas de clases

# Detección automática de fuentes
SRC = $(SRC_DIR)/main.cc \
      $(foreach dir,$(CLASS_DIRS),$(wildcard $(SRC_DIR)/$(dir)/*.cc))

# Generación de objetos (manteniendo estructura de directorios)
OBJ = $(patsubst $(SRC_DIR)/%.cc,%.o,$(SRC))

# Regla principal
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Regla para clases en subdirectorios
%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(@D)  # Crea directorio para el .o si no existe
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

# Limpieza (ahora recursiva)
clean:
	rm -f $(TARGET)
	find . -name "*.o" -delete

.PHONY: all clean