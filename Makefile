CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -O2
TARGET = computer_builder
SRCDIR = src
BUILDDIR = build

SOURCES = $(wildcard $(SRCDIR)/*.cpp) \
          $(wildcard $(SRCDIR)/builder/*.cpp)

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: $(BUILDDIR) $(TARGET)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/builder

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run