#!/bin/bash
set -e

# Install required packages depending on the platform
if command -v apt-get >/dev/null; then
    sudo apt-get update
    sudo apt-get install -y build-essential cmake libsdl2-dev
elif command -v brew >/dev/null; then
    brew install cmake sdl2
elif command -v pacman >/dev/null; then
    sudo pacman -Sy --noconfirm cmake sdl2
else
    echo "Please install CMake and SDL2 development files using your package manager" >&2
fi

# Build project
mkdir -p FilamentSDL/build
cmake -S FilamentSDL -B FilamentSDL/build
cmake --build FilamentSDL/build -j $(nproc 2>/dev/null || sysctl -n hw.ncpu)
