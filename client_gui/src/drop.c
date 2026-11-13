/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:38:46 by msturma           #+#    #+#             */
/*   Updated: 2026/11/13 14:38:47 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "inventory.h"
#include "notification.h"
#include <raylib.h>
#include <stdio.h>

Rectangle	get_drop_button(Rectangle panel, int i)
{
	return ((Rectangle){
		panel.x + panel.width - 45,
		panel.y + 65 + i * 30,
		24,
		24
	});
}

void	drop_button(Rectangle button)
{
	DrawRectangleRec(button, RED);
	DrawText("X", button.x + 6, button.y + 3, 18, WHITE);
}

void	handle_inventory_drop(t_game *game)
{
	Rectangle	panel;
	Rectangle	button;
	char		cmd[256];
	int			i;

	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		return ;
	panel = get_inventory_panel();
	i = 0;
	while (game->inventory[i])
	{
		button = get_drop_button(panel, i);
		if (CheckCollisionPointRec(GetMousePosition(), button))
		{
			snprintf(cmd, sizeof(cmd), "DROP %s\n", game->inventory[i]);
			client_send(game->manager->client, cmd);
			game->state = GAME_WAIT_DROP;
			return ;
		}
		i++;
	}
}

void	wait_drop(t_game *game, char *buf)
{
	char	item[128];

	if (game->state != GAME_WAIT_DROP)
		return ;
	if (strncmp(buf, "OK ", 3) == 0)
	{
		strcpy(item, buf + 11);
		item[strlen(item) - 1] = '\0';
		add_item(game, item);
		client_send(game->manager->client, "INVENTORY\n");
		game->state = GAME_WAIT_INVENTORY;
		return ;
	}
	show_notification(game, buf);
	game->state = GAME_IDLE;
}
