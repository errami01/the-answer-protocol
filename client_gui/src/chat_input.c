/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chat_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 12:26:44 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 12:37:09 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chat.h"

void	init_chat_input(t_game *game)
{
	game->chat_input[0] = '\0';
	game->chat_input_len = 0;
	game->chat_input_active = 0;
	game->chat_mode = CHAT_MODE_GLOBAL;
}

Rectangle	get_chatbox(void)
{
	int	width;
	int	height;
	int	margin;

	width = 300;
	height = 240;
	margin = 20;
	return ((Rectangle){
		GetScreenWidth() - width - margin,
		GetScreenHeight() - height - margin,
		width,
		height
	});
}

Rectangle	get_chat_input(void)
{
	Rectangle	chat;

	chat = get_chatbox();
	return ((Rectangle){
		chat.x + 10,
		chat.y + chat.height - 40,
		chat.width - 20,
		30
	});
}

void	draw_chat_input(t_game *game)
{
	Rectangle	input;
	Color		border;

	input = get_chat_input();
	if (game->chat_input_active)
		border = BLUE;
	else
		border = DARKGRAY;
	DrawRectangleRec(input, WHITE);
	DrawRectangleLinesEx(input, 1, border);
	if (game->chat_input_len == 0)
		DrawText("Type a message...", input.x + 8, input.y + 7, 16, GRAY);
	else
		DrawText(game->chat_input, input.x + 8, input.y + 7, 16, BLACK);
}
