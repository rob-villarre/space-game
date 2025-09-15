CC = g++
EMCC = em++

SRC = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, build/%.o, $(SRC))

TARGET = bin/desktop/raylib.exe
WEB_TARGET = bin/web/raylib.html

CFLAGS = -I include -c -Wall
LDFLAGS = -L lib -lraylib -lgdi32 -lwinmm

RAYLIB_DIR ?= ../raylib
SHELL_FILE = $(RAYLIB_DIR)/src/minshell.html
WEB_LIB = $(RAYLIB_DIR)/src/libraylib.web.a

# Emscripten flags
EMCC_CFLAGS = -Wall -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os \
	-I include -I $(RAYLIB_DIR)/src -I $(RAYLIB_DIR)/src/external

EMCC_LDFLAGS = -L lib -L $(RAYLIB_DIR)/src \
	-s USE_GLFW=3 \
	-s ASYNCIFY \
	-s TOTAL_MEMORY=67108864 \
	-s FORCE_FILESYSTEM=1 \
	--preload-file ./src/assets \
	--shell-file $(SHELL_FILE) \
	$(WEB_LIB) -DPLATFORM_WEB \
	-s 'EXPORTED_FUNCTIONS=["_free","_malloc","_main"]' \
	-s EXPORTED_RUNTIME_METHODS=ccall

all: desktop

# Desktop build
desktop: build_dirs $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

# Web build
web: build_dirs $(WEB_TARGET)

$(WEB_TARGET): $(SRC)
	$(EMCC) -o $(WEB_TARGET) $(SRC) $(EMCC_CFLAGS) $(EMCC_LDFLAGS)

# Rule to create all necessary build directories.
.PHONY: build_dirs
build_dirs:
	@mkdir -p bin
	@mkdir -p bin/web
	@mkdir -p bin/desktop
	@mkdir -p build

clean:
	rm -rf bin build
