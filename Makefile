CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -O2
TARGET = computer_builder

# Директории
SRCDIR = src
BUILDDIR = build

# Все .cpp файлы в проекте
SOURCES = $(SRCDIR)/main.cpp \
          $(SRCDIR)/core/PriceCatalog.cpp

# Объектные файлы (если нужны)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Правило по умолчанию
all: $(TARGET)
	./$(TARGET)

# Линковка
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) $(SOURCES) -o $(TARGET)

# Правило для компиляции .cpp в .o (опционально)
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) -c $< -o $@

# Очистка
clean:
	rm -f $(TARGET)
	rm -rf $(BUILDDIR)

# Только запуск
run: $(TARGET)
	./$(TARGET)

# Отладка
debug: CXXFLAGS += -g -DDEBUG
debug: clean $(TARGET)
	gdb ./$(TARGET)

# Проверка утечек памяти (Linux)
valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

# Установка флагов санитайзеров
sanitize: CXXFLAGS += -fsanitize=address -g
sanitize: clean $(TARGET)

# Для Windows (MinGW)
win: CXX = g++
win: CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -O2
win: 
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) $(SOURCES) -o $(TARGET).exe
	$(TARGET).exe

# Вывод помощи
help:
	@echo "Available targets:"
	@echo "  make          - Compile and run"
	@echo "  make clean    - Remove compiled files"
	@echo "  make run      - Run existing executable"
	@echo "  make debug    - Compile with debug symbols"
	@echo "  make valgrind - Check for memory leaks (Linux)"
	@echo "  make sanitize - Compile with address sanitizer"
	@echo "  make win      - Compile for Windows (MinGW)"
	@echo "  make help     - Show this help"

.PHONY: all clean run debug valgrind sanitize win help