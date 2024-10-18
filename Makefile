# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Source files
SOURCES = main.cpp LoadBalancer.cpp Request.cpp WebServer.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE = load_balancer

# Default target
all: $(EXECUTABLE)

# Link object files to create executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean up generated files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
