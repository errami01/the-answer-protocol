/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:19:34 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:19:35 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "game_arrows.h"
#include "game_components.h"
#include "notification.h"
#include "hp.h"

void	draw_arrows(t_game *game, int center_x, int center_y)
{
	if (game->current->north[0] != '\0')
	{
		draw_arrow_up(center_x, center_y - 100, game->current->north);
	}
	if (strlen(game->current->south) > 0)
	{
		draw_arrow_down(center_x, center_y + 100, game->current->south);
	}
	if (game->current->west[0] != '\0')
	{
		draw_arrow_left(center_x - 150, center_y, game->current->west);
	}
	if (game->current->east[0] != '\0')
	{
		draw_arrow_right(center_x + 150, center_y, game->current->east);
	}
}

void	draw_game_utils(t_game *game)
{
	draw_hp_bar(game);
	draw_items(game);
	draw_npcs(game);
	draw_notification(game);
}
