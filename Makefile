# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Object files
OBJ = 7a.o 7b.o

# Executable name
TARGET = program

# Default target to build the executable
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Compile 7a.cpp to 7a.o
7a.o: 7a.cpp
	$(CXX) $(CXXFLAGS) -c 7a.cpp

# Compile 7b.cpp to 7b.o
7b.o: 7b.cpp
	$(CXX) $(CXXFLAGS) -c 7b.cpp

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)
