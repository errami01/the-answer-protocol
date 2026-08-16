CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./shared
SERVER_SRC = server/main.c
SERVER_OBJ = $(SERVER_SRC:.c=.o)
NAME = server_app

all: $(NAME)

$(NAME): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o $(NAME)

clean:
	rm -f $(SERVER_OBJ) $(NAME)

re: clean all