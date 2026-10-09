#include "npc.h"

void talk(t_game *game, const char *npc)
{
    char cmd[256];

    snprintf(
        cmd,
        sizeof(cmd),
        "TALK %s\n",
        npc
    );

    game->npc_response[0] = '\0';

    if (client_send(game->manager->client, cmd) < 0)
        return ;

    game->state = GAME_WAIT_TALK;
}

void quest(t_game *game, const char *npc)
{
    char cmd[256];

    snprintf(
        cmd,
        sizeof(cmd),
        "QUEST %s\n",
        npc
    );

    if (client_send(game->manager->client, cmd) < 0)
        return ;
}

void attack(t_game *game, const char *npc)
{
    char cmd[256];

    snprintf(
        cmd,
        sizeof(cmd),
        "ATTACK %s\n",
        npc
    );

    if (client_send(game->manager->client, cmd) < 0)
        return ;
}
