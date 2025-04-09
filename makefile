# Makefile para proyecto Tetris
CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++17 -I. -IScreen -IScene $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf
TARGET = tetris

# Detección de fuentes
SRC = $(shell find Screen Font Button Scene constants -name '*.cc') main.cc

# Generación de objetos
OBJ = $(SRC:.cc=.o)

# Regla principal
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Regla implícita para compilar .cc a .o
%.o: %.cc
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpieza
clean:
	rm -f $(TARGET)
	find . -name "*.o" -delete

.PHONY: all clean