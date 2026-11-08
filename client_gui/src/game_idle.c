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
#include "players.h"
#include "group.h"

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

static void	handle_players(t_game *game)
{
	if (IsKeyPressed(KEY_TAB))
	{
		if (game->players_open)
			game->players_open = 0;
		else
			players(game);
	}
}

static void	handle_quests(t_game *game)
{
	if (IsKeyPressed(KEY_Q))
	{
		if (game->quests_open)
			game->quests_open = 0;
		else
			quests(game);
	}
}

void	game_idle(t_game *game, char *buf)
{
	if (game->state == GAME_IDLE)
	{
		handle_inventory(game);
		handle_players(game);
		handle_quests(game);
		handle_group_window(game);
		if (game->npc_open)
			handle_npc_dialog(game);
		if (game->inventory_open || game->players_open
			|| game->quests_open || game->npc_open)
			return ;
		handle_movement_buttons(game);
		handle_item_clicks(game);
	}
}
