#!/bin/bash

set -e

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
RAYLIB_DIR="$ROOT_DIR/client_gui/lib/raylib"
INSTALL_DIR="$RAYLIB_DIR/client_gui/install"

if [ -f "$INSTALL_DIR/include/raylib.h" ] && \
   [ -f "$INSTALL_DIR/lib/libraylib.a" ]; then
    echo "raylib is already installed."
    exit 0
fi

if [ ! -d "$RAYLIB_DIR/.git" ]; then
    echo "Cloning raylib..."
    git clone --depth 1 --branch 5.5 \
        https://github.com/raysan5/raylib.git "$RAYLIB_DIR"
fi

echo "Configuring raylib..."
cmake -S "$RAYLIB_DIR" -B "$RAYLIB_DIR/build" \
    -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR" \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_EXAMPLES=OFF

echo "Building raylib..."
cmake --build "$RAYLIB_DIR/build" --parallel 4

echo "Installing raylib..."
cmake --install "$RAYLIB_DIR/build"
