# Define the C++ compiler to use
CXX = g++

# Define any compile-time flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Define any directories containing header files
INCLUDES = -Iinclude

# Define library paths and libraries
LIBS  = -lraylib -lGL -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lm -lpthread -ldl -lrt

# Define the C++ source files
SRCS = $(wildcard src/*.cpp)

# Define the executable file name
TARGET = dino_game

# The default rule that builds everything
all: $(TARGET)

# Rule to link the program
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(SRCS) $(LIBS)

# Rule to clean up the project
clean:
	rm -f $(TARGET)
