/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chat_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 12:26:49 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 12:37:58 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chat.h"

Rectangle	get_chat_tab(int index)
{
	Rectangle	chat;

	chat = get_chatbox();
	return ((Rectangle){
		chat.x + 10 + index * 90,
		chat.y + 10,
		80,
		25
	});
}

void	draw_chat_tabs(t_game *game)
{
	Rectangle	global;
	Rectangle	room;
	Color		color_global;
	Color		color_room;

	global = get_chat_tab(0);
	room = get_chat_tab(1);
	if (game->chat_mode == CHAT_MODE_GLOBAL)
	{
		color_global = GRAY;
		color_room = LIGHTGRAY;
	}
	else
	{
		color_room = GRAY;
		color_global = LIGHTGRAY;
	}
	DrawRectangleRec(global, color_global);
	DrawRectangleRec(room, color_room);
	DrawRectangleLinesEx(global, 1, DARKGRAY);
	DrawRectangleLinesEx(room, 1, DARKGRAY);
	DrawText("Global", global.x + 10, global.y + 5, 16, BLACK);
	DrawText("Room", room.x + 10, room.y + 5, 16, BLACK);
}
