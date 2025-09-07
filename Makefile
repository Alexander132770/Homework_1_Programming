# ==============================================================================
# Makefile для C++ проекта (файлы в корне)
# ==============================================================================

# --- Конфигурация проекта ---
TARGET = rpn_calculator
BUILD_DIR = build

# Исходные файлы в корневой директории
SOURCES = main.cpp rpn.cpp
OBJECTS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)

# --- Компилятор и флаги ---
CXX = g++
CXX_STANDARD = c++17

# Базовые флаги
CXXFLAGS_BASE = -std=$(CXX_STANDARD) -Wall -Wextra -Wpedantic

# Конфигурации сборки
CXXFLAGS_DEBUG = $(CXXFLAGS_BASE) -g -O0
CXXFLAGS_RELEASE = $(CXXFLAGS_BASE) -O3 -DNDEBUG
CXXFLAGS_SANITIZE = $(CXXFLAGS_BASE) -g -O0 -fsanitize=address,undefined -fno-omit-frame-pointer

LDFLAGS_SANITIZE = -fsanitize=address,undefined

# --- Правила сборки ---
.DEFAULT_GOAL := debug

debug: CXXFLAGS = $(CXXFLAGS_DEBUG)
debug: $(BUILD_DIR)/$(TARGET)

release: CXXFLAGS = $(CXXFLAGS_RELEASE)
release: $(BUILD_DIR)/$(TARGET)

sanitize: CXXFLAGS = $(CXXFLAGS_SANITIZE)
sanitize: LDFLAGS = $(LDFLAGS_SANITIZE)
sanitize: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Сборка завершена: $@"

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $@

# --- Вспомогательные правила ---
clean:
	rm -rf $(BUILD_DIR)
	@echo "Очистка завершена"

run: debug
	./$(BUILD_DIR)/$(TARGET) input.txt output.txt

.PHONY: all debug release sanitize clean run
