/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:20:13 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:49:27 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raylib.h>
#include "inventory.h"
#include "game.h"

static Rectangle	get_inventory_panel(void)
{
	int	width;
	int	height;

	width = 400;
	height = 350;
	return ((Rectangle){
		(GetScreenWidth() - width) / 2,
		(GetScreenHeight() - height) / 2,
		width,
		height
	});
}

static void	inventory_label(Rectangle panel, char **items)
{
	DrawText("Inventory",
		panel.x + (panel.width - MeasureText("Inventory", 28)) / 2,
		panel.y + 20, 28, BLACK);
	if (items == NULL || items[0] == NULL)
	{
		DrawText("Inventory is empty",
			panel.x + (panel.width
				- MeasureText("Inventory is empty", 18)) / 2,
			panel.y + 100, 18, GRAY);
		return ;
	}
}

void	draw_inventory(char **items)
{
	Rectangle	panel;
	int			i;

	panel = get_inventory_panel();
	DrawRectangle(0, 0, GetScreenWidth(),
		GetScreenHeight(), Fade(BLACK, 0.55f));
	DrawRectangleRec(panel, RAYWHITE);
	DrawRectangleLinesEx(panel, 2, RAYWHITE);
	inventory_label(panel, items);
	i = 0;
	while (items[i] != NULL)
	{
		DrawText(items[i], panel.x + 30,
			panel.y + 80 + i * 30, 20, BLACK);
		i++;
	}
}

void	clear_inventory(t_game *game)
{
	int	i;

	i = 0;
	while (i < MAX_INVENTORY && game->inventory[i] != NULL)
	{
		free(game->inventory[i]);
		game->inventory[i] = NULL;
		i++;
	}
}
