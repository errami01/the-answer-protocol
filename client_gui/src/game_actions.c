#include "game.h"
#include "quest.h"
#include "attack.h"
#include "inventory.h"
#include "game_utils.h"
#include "hp.h"

void	wait_npc_action(t_game *game, char *buf)
{
	if (game->state == GAME_WAIT_TALK)
	{
		strncpy(game->npc_response, buf + 3, sizeof(game->npc_response) - 1);
		game->npc_response[sizeof(game->npc_response) - 1] = '\0';
		game->state = GAME_IDLE;
	}
	if (game->state == GAME_WAIT_QUEST)
		quest_state(game, buf);
	if (game->state == GAME_WAIT_ATTACK)
		attack_state(game, buf);
}

void	wait_menus(t_game *game, char *buf)
{
	if (game->state == GAME_WAIT_INVENTORY)
	{
		if (parse_inventory(buf, game) < 0)
		{
			game->state = GAME_IDLE;
			return ;
		}
		game->inventory_open = 1;
		game->state = GAME_IDLE;
	}
	if (game->state == GAME_WAIT_QUESTS)
	{
		if (parse_quests(buf, game) < 0)
		{
			game->state = GAME_IDLE;
			return ;
		}
		game->quests_open = 1;
		game->state = GAME_IDLE;
	}
}

void	wait_move(t_game *game, char *buf)
{
	t_room	*room;

	if (game->state == GAME_WAIT_MOVE)
	{
		if (strncmp(buf, "OK room=", 8) == 0)
		{
			client_send(game->manager->client, "LOOK\n");
			game->state = GAME_WAIT_LOOK;
		}
	}
	if (game->state == GAME_WAIT_LOOK)
	{
		room = malloc(sizeof(*room));
		if (!room)
			return ;
		if (parse_look(buf, room) < 0)
		{
			free(room);
			return ;
		}
		free(game->current);
		game->current = room;
		game->state = GAME_IDLE;
	}
}

void	wait_status(t_game *game, char *buf)
{
	if (game->state == GAME_WAIT_STATUS)
	{
		if (parse_status(buf, game) < 0)
			return ;
		game->state = GAME_IDLE;
	}
}

void	wait_take(t_game *game, char *buf)
{
	if (game->state == GAME_WAIT_TAKE)
	{
		if (strncmp(buf, "OK taken=", 9) == 0)
		{
			client_send(game->manager->client, "LOOK\n");
			game->state = GAME_WAIT_LOOK;
		}
	}
}
