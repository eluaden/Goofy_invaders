# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -std=c++11

# Source files
SRCS = main.cpp


# Default target
all: space_invaders

# Link object files to create the executable
space_invaders: main.cpp player.o enemies.o
	g++ main.cpp player.o enemies.o -o space_invaders $(CXXFLAGS)
player.o: player.cpp player.h
	g++ -c player.cpp -o player.o $(CXXFLAGS)
enemies.o: enemies.cpp enemies.h
	g++ -c enemies.cpp -o enemies.o $(CXXFLAGS)
# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean