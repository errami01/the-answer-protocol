cmake_minimum_required(VERSION 3.20)

project(my_game C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(my_game
    src/main.c
    src/manager.c
    src/login.c
    src/client.c
    src/game.c
    src/game_arrows.c
    src/game_arrow_buttons.c
    src/game_utils.c
    src/game_commands.c
    src/game_components.c
    src/game_components_utils.c
    src/inventory.c
)

target_link_libraries(my_game PRIVATE raylib)

target_compile_options(my_game PRIVATE
    -g
    -fsanitize=address
    -fno-omit-frame-pointer
)

target_link_options(my_game PRIVATE
    -fsanitize=address
)
