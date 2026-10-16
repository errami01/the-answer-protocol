#include "quest.h"
#include "game_utils.h"

int	parse_quest(const char *response, t_game *game)
{
	if (extract_json_string(response,
			"desc", game->npc_response,
			sizeof(game->npc_response)) < 0)
	{
        if (strncmp(response, "OK Quest Completed!", 19) == 0)
        {
            if (client_send(game->manager->client, "STATUS\n") < 0)
                return (-1);
		    strncpy(game->npc_response, response + 3, sizeof(game->npc_response));
		    game->npc_response[sizeof(game->npc_response) - 1] = '\0';
            game->state = GAME_WAIT_STATUS;
            return (1);
        }
		strncpy(game->npc_response, response + 3, sizeof(game->npc_response));
		game->npc_response[sizeof(game->npc_response) - 1] = '\0';
	}
	return (0);
}

void quest_state(t_game *game, char *buf)
{
    int result;

    result = parse_quest(buf, game);
    if (result < 0)
    {
        game->state = GAME_IDLE;
        return ;
    }

    if (result == 1)
        return ;

    game->state = GAME_IDLE;
}
