/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:37:45 by msturma           #+#    #+#             */
/*   Updated: 2026/11/13 14:53:18 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "group.h"
#include <raylib.h>

void	init_group_window(t_game *game)
{
	game->group_window_open = 0;
	game->group_joined = 0;
	game->group_leader[0] = '\0';
}

void	draw_group_window(t_game *game)
{
	Rectangle	panel;

	panel = get_group_window_panel();
	DrawRectangle(0, 0, GetScreenWidth(),
		GetScreenHeight(), Fade(BLACK, 0.55f));
	DrawRectangleRec(panel, RAYWHITE);
	DrawRectangleLinesEx(panel, 2, RAYWHITE);
	DrawText("Group", (GetScreenWidth()
			- MeasureText("Group", 24)) / 2, panel.y + 20, 24, BLACK);
	if (!game->group_joined)
		draw_not_in_group(game, panel);
	else
		draw_in_group(game, panel);
}

void	handle_group_window(t_game *game)
{
	if (game->inventory_open || game->quests_open
		|| game->players_open || game->npc_open)
		return ;
	if (IsKeyPressed(KEY_G))
	{
		if (game->group_window_open)
			game->group_window_open = 0;
		else
			game->group_window_open = 1;
	}
}

void	handle_group_actions(t_game *game)
{
	handle_group_invite(game);
	handle_group_create(game);
	handle_group_input_pointer(game);
	handle_group_leave(game);
	handle_group_input(game);
	handle_group_invite_submit(game);
}

void	wait_group(t_game *game, char *buf)
{
	wait_group_create(game, buf);
	wait_group_leave(game, buf);
	wait_group_invite_submit(game, buf);
}
