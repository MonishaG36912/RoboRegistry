# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./src

# Source and object files
SRCDIR = src
OBJDIR = obj
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Target executable
TARGET = robot_program

# Default rule
all: $(OBJDIR) $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS) main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile main.cpp
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile source files in src/
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean compiled files
clean:
	rm -rf $(OBJDIR)/*.o main.o $(TARGET)

.PHONY: all clean
