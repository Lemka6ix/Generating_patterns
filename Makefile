CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2
TARGET = computer_builder
SOURCES = main.cpp core/PriceCatalog.cpp

all:
	$(CXX) $(CXXFLAGS) -I. $(SOURCES) -o $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

docs:
	doxygen Doxyfile

.PHONY: all clean run docs