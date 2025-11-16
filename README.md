# space-game

A small 2D space shooter demo built with C++ and CMake. The project uses a CMake-based build system and vcpkg for dependency management.

## Contents

- `src/` — game source code and assets
- `include/` — public headers
- `build/` — build artifacts (when you build the project)
- `CMakeLists.txt` — top-level CMake project file

## Quick overview

This README explains how to build and run the game on Desktop (Windows) and how to produce a Web (WebAssembly) build using Emscripten. I make a few small assumptions below — if your CMake setup differs, see the Troubleshooting section.

## Prerequisites

### Desktop (Windows)
- CMake (>= 4.4.1)
- vcpkg
- w64devkit

### Web (WASM)
- Emscripten SDK (emsdk). Install and activate it following the official instructions: https://emscripten.org/docs/getting_started/downloads.html

### Cmake

Create `CmakeUserPresets.json` and set varaibles as shown in `CmakeUserPresets.json.example`

---

## Desktop build (Windows)

```powershell
# Configure & generate with the 'desktop' preset
cmake --preset desktop
# Build using the same preset
cmake --build .\build\desktop
```

Run the game

```powershell
# Example: run the built exe directly
& "${PWD}\build\space-game\space-game.exe"
# Or if built to build/desktop:
& "${PWD}\build\desktop\space-game.exe"
```

---

## Web build (WebAssembly) — Emscripten

```powershell
# Configure & generate with the 'desktop' preset
cmake --preset web
# Build using the same preset
cmake --build .\build\web
```

Run the web build locally

```powershell
cd build/web
python -m http.server 8000
# Then open http://localhost:8000/space-game.html in your browser
```

## Credits

- Asset pack: Kenney (see `src/assets/kenneyshmup/License.txt`)
