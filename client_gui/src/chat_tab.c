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
#include "game.h"
#include <raylib.h>

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

static void	set_colors(t_game *game, Color *colors)
{
	if (game->chat_mode == CHAT_MODE_GLOBAL)
	{
		colors[0] = GRAY;
		colors[1] = LIGHTGRAY;
		colors[2] = LIGHTGRAY;
	}
	if (game->chat_mode == CHAT_MODE_ROOM)
	{
		colors[0] = LIGHTGRAY;
		colors[1] = GRAY;
		colors[2] = LIGHTGRAY;
	}
	if (game->chat_mode == CHAT_MODE_GROUP)
	{
		colors[0] = LIGHTGRAY;
		colors[1] = LIGHTGRAY;
		colors[2] = GRAY;
	}
}

void	draw_chat_tabs(t_game *game)
{
	Rectangle	global;
	Rectangle	room;
	Rectangle	group;
	Color		colors[3];

	global = get_chat_tab(0);
	room = get_chat_tab(1);
	group = get_chat_tab(2);
	set_colors(game, colors);
	DrawRectangleRec(global, colors[0]);
	DrawRectangleRec(room, colors[1]);
	DrawRectangleLinesEx(global, 1, DARKGRAY);
	DrawRectangleLinesEx(room, 1, DARKGRAY);
	DrawText("Global", global.x + 10, global.y + 5, 16, BLACK);
	DrawText("Room", room.x + 10, room.y + 5, 16, BLACK);
	if (game->group_joined)
	{
		DrawRectangleRec(group, colors[2]);
		DrawRectangleLinesEx(group, 1, DARKGRAY);
		DrawText("Group", group.x + 10, group.y + 5, 16, BLACK);
	}
}
