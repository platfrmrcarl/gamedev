# Compiler setup
CXX = g++
CXXFLAGS = -Wall -std=c++17 -g $(shell pkg-config --cflags sdl3)
LDFLAGS = $(shell pkg-config --libs sdl3)

# Source and Output
SRC = src/main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = game

# Default rule
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean