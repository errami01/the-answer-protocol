CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./shared
SERVER_SRC = server/main.c server/world_loader.c server/world_linker.c \
			server/cmd_look.c server/player.c server/events.c server/cmd_move.c \
			server/cmd_chat.c server/item_utils.c server/cmd_items.c \
			server/room_utils.c libs/jsmn.c server/cmd_status.c \
			server/cmd_attack.c server/death.c server/npc_utils.c
SERVER_OBJ = $(SERVER_SRC:.c=.o)
NAME = server_app

all: $(NAME)

$(NAME): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o $(NAME)

clean:
	rm -f $(SERVER_OBJ) $(NAME)

re: clean all