# CS5701 Project 3 - Generate Map

This project is an interactive terrain map generator built with SFML and CMake.
It creates a square map with user-selected size and terrain types, then improves the map using a min-conflicts style local search algorithm.

## Features

- Interactive UI for selecting:
	- Map size (`50x50`, `75x75`, `100x100`, `200x200`)
	- Terrain set (Water, Beach, Lowland, Forest, Hill, Ridges, Mountain, Snow Tops)
	- Diagonal constraints (`On`/`Off`)
	- Animation (`On`/`Off`)
- Random initial map generation
- Conflict-reduction algorithm that iteratively improves tile assignments
- Real-time map display and conflict status updates
- Assets copied automatically to the build output directory by CMake

## Tech Stack

- C++20
- CMake (3.22+)
- SFML 3 (Graphics, Window, System)

## Project Structure

- `src/` - Application and algorithm source files
- `include/` - Header files
- `assets/` - Runtime assets copied next to the executable
- `CMakeLists.txt` - Build configuration

## Prerequisites

Install the following before building:

- A C++ compiler with C++20 support
- CMake 3.22 or newer
- SFML 3 development package

## Environment Setup and Build

### Windows

1. Install tools:
	 - Visual Studio 2022 Build Tools (or full Visual Studio with C++)
	 - CMake 3.22+
	 - SFML 3.1.0 (or compatible SFML 3 release)
2. Ensure CMake can find SFML:
	 - Option A: install SFML to `C:/SFML-3.1.0` (matches current `CMakeLists.txt` default on Windows)
	 - Option B: pass one of these while configuring:
		 - `-DCMAKE_PREFIX_PATH="C:/path/to/SFML"`
		 - `-DSFML_DIR="C:/path/to/SFML/lib/cmake/SFML"`
3. Configure and build from the project root:

```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

4. Run:

```powershell
.\build\mapGenarator.exe
```

Notes:
- If you see `cannot open output file sfml-app.exe: Permission denied`, close any running `mapGenarator.exe` and rebuild.

### Linux

1. Install dependencies (Ubuntu/Debian example):

```bash
sudo apt update
sudo apt install -y build-essential cmake libsfml-dev
```

2. Configure and build from the project root:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

3. Run:

```bash
./build/sfml-app
```

If CMake cannot find SFML, configure with:

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/SFML
```

### macOS

1. Install tools (Homebrew example):

```bash
brew install cmake sfml
```

2. Configure and build from the project root:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

3. Run:

```bash
./build/sfml-app
```

If SFML is installed in a non-default location, configure with:

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH=/opt/homebrew
```

## How to Use

1. Launch the application.
2. Select map size and terrain types.
3. Click `Generate Map` to create an initial map.
4. Choose diagonal and animation options.
5. Click `Run` to start conflict reduction.
6. Watch status text for conflict counts, iterations, and completion/stuck state.

## Algorithm Summary

- The map is initialized with random terrain values.
- Each pass evaluates conflict counts for tiles relative to neighbors.
- The algorithm tries to reduce conflicts by assigning better local values.
- If stuck in a local minimum, it perturbs a high-conflict tile (and neighbors) to escape.

## Troubleshooting

- CMake cannot find SFML:
	- Pass `CMAKE_PREFIX_PATH` or `SFML_DIR` explicitly.
	- Clear/reconfigure the `build/` directory if cached paths are stale.
- Executable builds but does not run:
	- Ensure the `assets/` copy step completed.
- Build fails after app was running on Windows:
	- Stop the running executable and rebuild.
