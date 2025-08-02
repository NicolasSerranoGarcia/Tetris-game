CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++17 -I. -Isrc/Screen -Isrc/Scene $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image -lSDL2_mixer
TARGET = tetris

SRC = $(shell find src -name '*.cc')
OBJ = $(patsubst src/%.cc, build/%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ) resources.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

build/%.o: src/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -rf build

.PHONY: all clean
