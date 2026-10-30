CC ?= cc

BUILD_DIR := build
TARGET := $(BUILD_DIR)/sdl_training
TEST_TARGET := $(BUILD_DIR)/tests

SOURCES := $(wildcard src/*.c)
TEST_SOURCES := $(wildcard tests/*.c)
TEST_SUPPORT_SOURCES := $(filter-out src/main.c,$(SOURCES))

CPPFLAGS += -Isrc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2

SDL_CFLAGS := $(shell pkg-config --cflags sdl2 SDL2_ttf)
SDL_LIBS := $(shell pkg-config --libs sdl2 SDL2_ttf)
CRITERION_CFLAGS := $(shell pkg-config --cflags criterion)
CRITERION_LIBS := $(shell pkg-config --libs criterion)

.PHONY: all run test clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SDL_CFLAGS) $(LDFLAGS) -o $@ $(SOURCES) $(LDLIBS) $(SDL_LIBS)

run: $(TARGET)
	./$(TARGET)

test:
	@if [ -z "$(TEST_SOURCES)" ]; then \
		echo "No Criterion test sources found in tests/*.c"; \
		exit 1; \
	fi
	@pkg-config --exists criterion || { echo "Criterion development files were not found by pkg-config."; exit 1; }
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SDL_CFLAGS) $(CRITERION_CFLAGS) $(LDFLAGS) -o $(TEST_TARGET) $(TEST_SOURCES) $(TEST_SUPPORT_SOURCES) $(LDLIBS) $(SDL_LIBS) $(CRITERION_LIBS)
	./$(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR)
