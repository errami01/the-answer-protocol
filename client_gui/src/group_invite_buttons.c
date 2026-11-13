/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_invite_buttons.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:37:19 by msturma           #+#    #+#             */
/*   Updated: 2026/11/13 14:37:20 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "group.h"
#include <raylib.h>

void	draw_accept_icon(Rectangle button)
{
	float	x;
	float	y;

	x = button.x + button.width / 2;
	y = button.y + button.height / 2;
	DrawLineEx((Vector2){x - 8, y}, (Vector2){x - 2, y + 6}, 3, WHITE);
	DrawLineEx((Vector2){x - 2, y + 6}, (Vector2){x + 9, y - 7}, 3, WHITE);
}

void	draw_decline_icon(Rectangle button)
{
	float	x;
	float	y;

	x = button.x + button.width / 2;
	y = button.y + button.height / 2;
	DrawLineEx((Vector2){x - 7, y - 7}, (Vector2){x + 7, y + 7}, 3, WHITE);
	DrawLineEx((Vector2){x + 7, y + 7}, (Vector2){x - 7, y - 7}, 3, WHITE);
}

static void	accept_invite(t_game *game)
{
	char	command[MAX_PLAYER_NAME + 16];

	snprintf(command, sizeof(command), "GROUP JOIN %s\n",
		game->group_invite_sender);
	client_send(game->manager->client, command);
	game->state = GAME_WAIT_GROUP_INVITE_ACCEPT;
}

static void	handle_invite_click(t_game *game, Vector2 mouse)
{
	Rectangle	panel;
	Rectangle	accept;
	Rectangle	decline;

	panel = get_invite_panel();
	accept = get_accept_button(panel);
	decline = get_decline_button(panel);
	if (CheckCollisionPointRec(mouse, accept))
		accept_invite(game);
	if (CheckCollisionPointRec(mouse, decline))
	{
		game->group_invite_open = 0;
		game->group_invite_sender[0] = '\0';
	}
}

void	handle_group_invite(t_game *game)
{
	Vector2	mouse;

	if (!game->group_invite_open)
		return ;
	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		return ;
	mouse = GetMousePosition();
	handle_invite_click(game, mouse);
}
