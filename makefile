CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++17 -I. -IScreen -IScene $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image
TARGET = tetris

# Source detection
SRC = $(shell find Screen Font Button Scene Figures constants Image -name '*.cc') main.cc

#Object generation
OBJ = $(SRC:.cc=.o)

# Main rule
all: $(TARGET)

#tetris is dependent of all the binary files
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Implicit rule to compile independent files
%.o: %.cc
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	find . -name "*.o" -delete

.PHONY: all clean