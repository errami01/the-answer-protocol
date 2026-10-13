cmake -S ./raylib -B ./raylib/build \
    -DCMAKE_INSTALL_PREFIX="$PWD/raylib/install"

cmake --build ./raylib/build
cmake --install ./raylib/build
