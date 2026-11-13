/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:37:03 by msturma           #+#    #+#             */
/*   Updated: 2026/11/13 14:37:04 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "group.h"
#include "notification.h"

void	draw_group_input(t_game *game, Rectangle panel)
{
	Rectangle	input;
	Rectangle	button;
	Vector2		mouse;

	input = get_input_widget(panel);
	button = get_input_button(panel);
	mouse = GetMousePosition();
	if (CheckCollisionPointRec(mouse, input))
		DrawRectangleLines(input.x, input.y, input.width, input.height, BLUE);
	else
		DrawRectangleLines(input.x, input.y, input.width,
			input.height, DARKGRAY);
	if (game->group_invite_username_len < 27)
		DrawText(game->group_invite_username, input.x + 10,
			input.y + (input.height - 18) / 2, 18, DARKGRAY);
	else
		DrawText(game->group_invite_username + (game->group_invite_username_len
				- 27), input.x + 10,
			input.y + (input.height - 18) / 2, 18, DARKGRAY);
	if (CheckCollisionPointRec(mouse, button))
		DrawRectangleRec(button, DARKBLUE);
	else
		DrawRectangleRec(button, BLUE);
	DrawText("Invite", button.x + (button.width - MeasureText("Invite", 18))
		/ 2, button.y + (button.height - 18) / 2, 18, BLACK);
}

void	handle_group_input_pointer(t_game *game)
{
	Rectangle	panel;
	Rectangle	input;
	Vector2		mouse;

	if (!game->group_window_open || !game->group_joined)
		return ;
	panel = get_group_window_panel();
	input = get_input_widget(panel);
	mouse = GetMousePosition();
	if (CheckCollisionPointRec(mouse, input) && game->state == GAME_IDLE)
	{
		game->state = GAME_WAIT_GROUP_INPUT;
		return ;
	}
	if (!CheckCollisionPointRec(mouse, input)
		&& game->state == GAME_WAIT_GROUP_INPUT)
	{
		game->state = GAME_IDLE;
		return ;
	}
}

void	handle_group_input(t_game *game)
{
	int			key;
	int			input_y;
	Rectangle	button;

	if (game->state != GAME_WAIT_GROUP_INPUT)
		return ;
	key = GetCharPressed();
	while (key > 0)
	{
		if (key >= 32 && key <= 126 && game->group_invite_username_len < 63)
		{
			game->group_invite_username[
				game->group_invite_username_len++] = (char)key;
			game->group_invite_username[game->group_invite_username_len] = '\0';
		}
		key = GetCharPressed();
	}
	if (IsKeyPressed(KEY_BACKSPACE) && game->group_invite_username_len > 0)
	{
		game->group_invite_username_len--;
		game->group_invite_username[game->group_invite_username_len] = '\0';
	}
}

void	handle_group_invite_submit(t_game *game)
{
	Rectangle	panel;
	Rectangle	button;
	Vector2		mouse;
	char		cmd[64];

	if (!game->group_window_open || !game->group_joined)
		return ;
	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		return ;
	panel = get_group_window_panel();
	button = get_input_button(panel);
	mouse = GetMousePosition();
	if (CheckCollisionPointRec(mouse, button))
	{
		snprintf(cmd, sizeof(cmd), "GROUP INVITE %s\n",
			game->group_invite_username);
		client_send(game->manager->client, cmd);
		game->state = GAME_WAIT_GROUP_INVITE_SUBMIT;
	}
}

void	wait_group_invite_submit(t_game *game, char *buf)
{
	if (game->state != GAME_WAIT_GROUP_INVITE_SUBMIT)
		return ;
	if (strncmp(buf, "OK", 2) == 0)
	{
		game->group_invite_username[0] = '\0';
		game->group_invite_username_len = 0;
		game->state = GAME_IDLE;
		show_notification(game, "Invite sent.");
		return ;
	}
	game->state = GAME_IDLE;
	show_notification(game, "Failed to send an invite.");
}
