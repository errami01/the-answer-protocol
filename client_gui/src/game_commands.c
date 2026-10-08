#include "game_commands.h"
#include "client.h"
#include "game.h"
#include "game_utils.h"
#include <stdio.h>

void move(t_game *game, const char *direction)
{
    char cmd[64];

    snprintf(cmd, sizeof(cmd), "MOVE %s\n", direction);
    if (client_send(game->manager->client, cmd) < 0)
        return ;

    game->state = GAME_WAIT_MOVE;
}

void take(t_game *game, const char *item)
{
    char cmd[64];

    snprintf(cmd, sizeof(cmd), "TAKE %s\n", item);
    if (client_send(game->manager->client, cmd) < 0)
        return ;

    game->state = GAME_WAIT_TAKE;
}

void look(t_game *game)
{
    int bytes;
    char buf[BUFFER_SIZE];

    t_room *current = game->current;
    if (client_send(game->manager->client, "LOOK\n") < 0)
        return ;
    bytes = client_receive(game->manager->client, buf, sizeof(buf));
    if (bytes < 0)
        return ;

    t_room *room = malloc(sizeof(*room));
    if (!room)
        return ;
    if (parse_look(buf, room) < 0)
    {
        free(room);
        return ;
    }

    game->current = room;
    if (!current)
        free(current);
}

void inventory(t_game *game)
{
    if (client_send(game->manager->client, "INVENTORY\n") < 0)
        return ;

    game->state = GAME_WAIT_INVENTORY;
}
