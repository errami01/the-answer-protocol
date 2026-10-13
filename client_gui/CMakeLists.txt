cmake_minimum_required(VERSION 3.20)

project(client_gui C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(client_gui
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
    src/npc.c
    src/npc_actions.c
    src/quests.c
    
)

target_include_directories(client_gui PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/raylib/install/include
)

target_link_directories(client_gui PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/raylib/install/lib
)

target_link_libraries(client_gui PRIVATE
	raylib
	X11
	m
	pthread
	dl
	rt
)

target_compile_options(client_gui PRIVATE
    -g
    -fsanitize=address
    -fno-omit-frame-pointer
)

target_link_options(client_gui PRIVATE
    -fsanitize=address
)
