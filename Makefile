CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./shared
SERVER_SRC = server/main.c server/world_loader.c server/world_linker.c \
			server/cmd_look.c server/player.c server/events.c server/cmd_move.c \
			server/cmd_chat.c server/item_utils.c server/cmd_items.c \
			server/room_utils.c libs/jsmn.c server/cmd_status.c \
			server/cmd_attack.c server/death.c server/npc_utils.c \
			server/cmd_quest.c server/cmd_quests_list.c server/logger.c \
			server/disconnect.c server/abuse_monitor.c server/cmd_talk.c \
			server/group_utils.c server/cmd_group.c server/client_utils.c \
			server/cmd_connect.c server/room_cleanup.c server/cmd_who.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)
SERVER_NAME = server_app
CLIENT_NAME = client_app
CLIENT_SRC = client_cli/main.c client_cli/read_utils.c
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

all: $(SERVER_NAME) client

client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -o $(CLIENT_NAME)

raylib:
	@./client_gui/install.sh

client_gui: raylib
	@cmake -S client_gui -B client_gui/build
	@cmake --build client_gui/build --parallel 4

$(SERVER_NAME): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -lbsd -o $(SERVER_NAME)


clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean 
	rm -f $(SERVER_NAME) $(CLIENT_NAME)

re: fclean all
