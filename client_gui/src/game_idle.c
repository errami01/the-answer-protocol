#include "game.h"
#include "game_commands.h"
#include "npc.h"
#include "game_components.h"

void	game_idle(t_game *game, char *buf)
{
	if (game->state == GAME_IDLE)
	{
		if (IsKeyPressed(KEY_I))
		{
			if (game->inventory_open)
				game->inventory_open = 0;
			else
				inventory(game);
			return ;
		}
		if (IsKeyPressed(KEY_Q))
		{
			if (game->quests_open)
				game->quests_open = 0;
			else
				quests(game);
		}
		if (game->npc_open)
		{
			handle_npc_dialog(game);
			return ;
		}
		handle_movement_buttons(game);
		handle_item_clicks(game);
	}
}
