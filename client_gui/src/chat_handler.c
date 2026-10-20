/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chat_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 12:42:03 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 12:42:33 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chat.h"
#include "notification.h"

static void	handle_chat_click(t_game *game)
{
	Vector2	mouse;
	int		i;

	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		return ;
	mouse = GetMousePosition();
	game->chat_input_active = CheckCollisionPointRec(
			mouse,
			get_chat_input()
			);
	i = 0;
	while (i < 2)
	{
		if (CheckCollisionPointRec(mouse, get_chat_tab(i)))
		{
			game->chat_mode = (t_chat_mode)i;
			return ;
		}
		i++;
	}
}

static void	handle_chat_typing(t_game *game)
{
	int	key;

	if (!game->chat_input_active)
		return ;
	key = GetCharPressed();
	while (key > 0)
	{
		if (key >= 32 && key <= 126
			&& game->chat_input_len < CHAT_INPUT_SIZE - 1)
		{
			game->chat_input[game->chat_input_len++] = (char)key;
			game->chat_input[game->chat_input_len] = '\0';
		}
		key = GetCharPressed();
	}
	if (IsKeyPressed(KEY_BACKSPACE) && game->chat_input_len > 0)
	{
		game->chat_input_len--;
		game->chat_input[game->chat_input_len] = '\0';
	}
}

static void	send_chat_message(t_game *game)
{
	char	cmd[CHAT_INPUT_SIZE + 32];
	char	*channel;

	if (game->chat_input_len == 0)
		return ;
	if (game->chat_mode == CHAT_MODE_GLOBAL)
		channel = "GLOBAL";
	else
		channel = "ROOM";
	snprintf(cmd, sizeof(cmd), "CHAT %s %s\n", channel, game->chat_input);
	if (client_send(game->manager->client, cmd) < 0)
	{
		show_notification(game, "Failed to send message.");
		return ;
	}
	game->chat_input[0] = '\0';
	game->chat_input_len = 0;
}

void	handle_chat(t_game *game)
{
	handle_chat_click(game);
	handle_chat_typing(game);
	if (game->chat_input_active && IsKeyPressed(KEY_ENTER))
		send_chat_message(game);
}
