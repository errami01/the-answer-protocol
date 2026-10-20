/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:18:05 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 18:46:45 by msturma          ###   ########.fr       */
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
	Rectangle	chat;
	int			i;
	int			y;

	chat = get_chatbox();
	DrawRectangleRec(chat, RAYWHITE);
	DrawRectangleLinesEx(chat, 1, DARKGRAY);
	draw_chat_tabs(game);
	draw_chat_messages(game);
	draw_chat_input(game);
}
