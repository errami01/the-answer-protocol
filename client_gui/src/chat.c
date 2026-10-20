/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:18:05 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:18:06 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chat.h"

void	add_chat_message(t_game *game, const char *message)
{
	int	i;

	if (!game || !message)
		return ;
	if (game->chat_count < 8)
	{
		strncpy(game->chat[game->chat_count], message, 31);
		game->chat[game->chat_count][32 - 1] = '\0';
		game->chat_count++;
		return ;
	}
	i = 1;
	while (i < 8)
	{
		strcpy(game->chat[i - 1], game->chat[i]);
		i++;
	}
	strncpy(game->chat[7], message, 31);
	game->chat[7][31] = '\0';
}

void	draw_chat(t_game *game)
{
	int	x;
	int	y;
	int	i;

	x = GetScreenWidth() - WIDTH - MARGIN;
	y = GetScreenHeight() - HEIGHT - MARGIN;
	DrawRectangle(x, y, WIDTH, HEIGHT, Fade(RAYWHITE, 0.9f));
	DrawRectangleLines(x, y, WIDTH, HEIGHT, DARKGRAY);
	DrawText("Chat", x + PADDING, y + PADDING, 18, BLACK);
	i = 0;
	while (i < game->chat_count)
	{
		DrawText(game->chat[i], x + PADDING,
			y + 40 + i * LINE_HEIGHT, FONT_SIZE, DARKGRAY);
		i++;
	}
}
