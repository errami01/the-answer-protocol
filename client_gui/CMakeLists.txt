cmake_minimum_required(VERSION 3.20)

project(client_gui C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(client_gui
    src/attack.c
    src/chat.c
    src/chat_handler.c
    src/chat_input.c
    src/chat_message_wrap.c
    src/chat_scroll.c
    src/chat_tab.c
    src/client.c
    src/game_actions.c
    src/game_arrow_buttons.c
    src/game_arrows.c
    src/game.c
    src/game_commands.c
    src/game_components.c
    src/game_components_utils.c
    src/game_draw.c
    src/game_idle.c
    src/game_utils.c
    src/hp.c
    src/inventory.c
    src/inventory_parser.c
    src/json_parser.c
    src/login.c
    src/login_draw.c
    src/login_update.c
    src/main.c
    src/manager.c
    src/notification.c
    src/npc_actions.c
    src/npc.c
    src/npc_dialog_draw.c
    src/npc_text_wrap.c
    src/quest.c
    src/quests_draw.c
    src/quests_parser.c
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
