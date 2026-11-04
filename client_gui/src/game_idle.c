/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_idle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:19:46 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:19:47 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "game_commands.h"
#include "npc.h"
#include "game_components.h"
#include "inventory.h"

static void	handle_inventory(t_game *game)
{
	if (game->inventory_open)
		handle_inventory_drop(game);
	if (IsKeyPressed(KEY_I))
	{
		if (game->inventory_open)
			game->inventory_open = 0;
		else
			inventory(game);
	}
	return ;
}

void	game_idle(t_game *game, char *buf)
{
	if (game->state == GAME_IDLE)
	{
		handle_inventory(game);
		if (IsKeyPressed(KEY_Q))
		{
			if (game->quests_open)
				game->quests_open = 0;
			else
				quests(game);
		}
		if (game->npc_open)
			handle_npc_dialog(game);
		handle_movement_buttons(game);
		handle_item_clicks(game);
	}
}
