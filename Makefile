# Makefile for compiling a C++ program with GLFW and OpenGL

CXX = g++
CXXFLAGS = -std=c++11 -Wall -static-libstdc++

INCLUDE_DIR = include
LIB_DIR = lib

LIBS = -lglfw3 -lopengl32 -lgdi32

SRCS = $(wildcard *.cpp)

OUTPUT = a

# Build rule
$(OUTPUT): $(SRCS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -L$(LIB_DIR) $^ $(LIBS) -o $@

# Clean rule
clean:
	rm -f $(OUTPUT)

# Phony target to avoid conflicts with files named 'clean'
.PHONY: clean
