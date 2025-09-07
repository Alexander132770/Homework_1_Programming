
TARGET = rpn_calculator
SRC_DIR = src
BUILD_DIR = build


SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)


CXX = g++
CXX_STANDARD = c++17


CXXFLAGS_BASE = -std=$(CXX_STANDARD) -Wall -Wextra -Wpedantic -I$(SRC_DIR)


CXXFLAGS_DEBUG = $(CXXFLAGS_BASE) -g -O0
CXXFLAGS_RELEASE = $(CXXFLAGS_BASE) -O3 -DNDEBUG
CXXFLAGS_SANITIZE = $(CXXFLAGS_BASE) -g -O0 -fsanitize=address,undefined -fno-omit-frame-pointer

LDFLAGS_SANITIZE = -fsanitize=address,undefined


CLANG_TIDY = clang-tidy
CLANG_TIDY_FLAGS = --quiet -checks=bugprone-*,clang-analyzer-*,performance-*,portability-*,readability-*,-readability-magic-numbers

CLANG_FORMAT = clang-format
CLANG_FORMAT_FLAGS = -i --style=Google


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
	@echo " Сборка завершена: $@"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $@


lint:
	$(CLANG_TIDY) $(SOURCES) -- $(CXXFLAGS_BASE) $(CLANG_TIDY_FLAGS)
	@echo " Lint проверка пройдена"

format:
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SOURCES) $(wildcard $(SRC_DIR)/*.hpp)
	@echo " Форматирование завершено"

check-format:
	$(CLANG_FORMAT) --dry-run --Werror --style=Google $(SOURCES) $(wildcard $(SRC_DIR)/*.hpp)
	@echo " Форматирование корректно"

clean:
	rm -rf $(BUILD_DIR)
	@echo " Очистка завершена"

run: debug
	./$(BUILD_DIR)/$(TARGET) input.txt output.txt

run-sanitize: sanitize
	./$(BUILD_DIR)/$(TARGET) input.txt output.txt

ci-build: debug
	@echo " Запуск CI-теста..."
	./$(BUILD_DIR)/$(TARGET) input.txt output_ci.txt
	cat output_ci.txt

ci-lint: lint

.PHONY: all debug release sanitize clean lint format check-format run run-sanitize ci-build ci-lint
