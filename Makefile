# Compiler setup
CXX = g++
CXXFLAGS = -Wall -std=c++17 -g -Isrc $(shell pkg-config --cflags sdl3)
LDFLAGS = $(shell pkg-config --libs sdl3)

# Source and Output
SRC = src/main.cpp \
      src/Core/Engine.cpp \
      src/Core/Camera.cpp \
      src/Core/TextureManager.cpp \
      src/Core/Level.cpp \
      src/Input/InputManager.cpp \
      src/Input/PlayerController.cpp \
      src/States/StateManager.cpp \
      src/Physics/Physics.cpp \
      src/Entities/GameObject.cpp \
      src/States/PlayState.cpp

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
	rm -f $(OBJ) $(TARGET) src/Core/*.o src/Input/*.o src/States/*.o src/Physics/*.o src/Entities/*.o

.PHONY: all clean