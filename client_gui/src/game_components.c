/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_components.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 15:50:02 by msturma           #+#    #+#             */
/*   Updated: 2026/10/13 16:34:52 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_components.h"
#include "game_commands.h"
#include <raylib.h>

static	Rectangle get_item_button(int index)
{
	int	width;
	int	height;
	int	spacing;
	int	margin;

	width = 180;
	height = 32;
	spacing = 8;
	margin = 20;
	return ((Rectangle){
			GetScreenWidth() - width - margin,
			50 + index * (height + spacing),
			width,
			height
			});
}

static	int get_npc_start_y(t_game *game)
{
	int	items_start_y;
	int	items_height;

	items_start_y = 50;
	items_height =
		game->current->item_count
		* (LIST_HEIGHT + LIST_SPACING);
	return (items_start_y + items_height + 30);
}

Rectangle	get_npc_button(t_game *game, int index)
{
	int	start_y;

	start_y = get_npc_start_y(game);
	return ((Rectangle){
			GetScreenWidth() - LIST_WIDTH - LIST_MARGIN,
			start_y + 30 + index * (LIST_HEIGHT + LIST_SPACING),
			LIST_WIDTH,
			LIST_HEIGHT
			});
}

void	draw_items(t_game *game)
{
	int	i;
	Rectangle	rect;
	Vector2		mouse;
	Color		color;

	DrawText(
			"Items",
			GetScreenWidth() - 200,
			20,
			20,
			BLACK
		);
	i = 0;
	while (i < game->current->item_count)
	{
		rect = get_item_button(i);
		mouse = GetMousePosition();
		color = LIGHTGRAY;
		if (CheckCollisionPointRec(mouse, rect))
		{
			color = GRAY;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				take(game, game->current->items[i]);
		}
		DrawRectangleRec(rect, color);
		DrawRectangleLinesEx(rect, 1, DARKGRAY);
		DrawText(
				game->current->items[i],
				rect.x + 10,
				rect.y + 8,
				16,
				BLACK
			);
		i++;
	}
}

void	draw_npcs(t_game *game)
{
	int	i;
	int	start_y;
	Rectangle	rect;
	Vector2		mouse;
	Color		color;

	start_y = get_npc_start_y(game);
	DrawText(
			"NPCs",
			GetScreenWidth() - 200,
			start_y,
			20,
			BLACK
		);
	i = 0;
	while (i < game->current->npc_count)
	{
		rect = get_npc_button(game, i);
		mouse = GetMousePosition();
		color = LIGHTGRAY;
		if (CheckCollisionPointRec(mouse, rect))
		{
			color = GRAY;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				game->npc_open = 1;
				strncpy(game->selected_npc, game->current->npcs[i], sizeof(game->selected_npc) - 1);
				game->selected_npc[sizeof(game->selected_npc) - 1] = '\0';
			}
		}
		DrawRectangleRec(rect, color);
		DrawRectangleLinesEx(rect, 1, DARKGRAY);
		DrawText(
				game->current->npcs[i],
				rect.x + 10,
				rect.y + 8,
				16,
				BLACK
			);
		i++;
	}
}
