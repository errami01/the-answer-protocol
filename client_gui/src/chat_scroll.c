/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chat_scroll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 17:37:43 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 19:09:09 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chat.h"

void	init_chat_scroll(t_game *game)
{
	game->chat_scroll = 0;
	game->chat_auto_scroll = 0;
}

static Rectangle	get_chat_messages_rect(void)
{
	Rectangle	chat;

	chat = get_chatbox();
	return ((Rectangle){
		chat.x + 10,
		chat.y + 45,
		chat.width - 20,
		chat.height - 95
	});
}

static int	get_chat_content_height(t_game *game, int width)
{
	int	height;
	int	i;

	height = 0;
	i = 0;
	while (i < game->chat_count)
	{
		height += draw_chat_message(
				game->chat[i],
				(Vector2){0, 0},
				width,
				false
				);
		height += 4;
		i++;
	}
	return (height);
}

void	draw_chat_messages(t_game *game)
{
	Rectangle	area;
	int			content_height;
	int			max_scroll;
	int			y;
	int			i;

	area = get_chat_messages_rect();
	content_height = get_chat_content_height(game, area.width);
	max_scroll = content_height - area.height;
	if (max_scroll < 0)
		max_scroll = 0;
	if (game->chat_auto_scroll)
		game->chat_scroll = 0;
	if (game->chat_scroll > max_scroll)
		game->chat_scroll = max_scroll;
	y = (int)area.y - max_scroll + (int)game->chat_scroll;
	BeginScissorMode((int)area.x, (int)area.y,
		(int)area.width, (int)area.height);
	i = 0;
	while (i < game->chat_count)
	{
		y += draw_chat_message(game->chat[i],
				(Vector2){area.x, y}, area.width, true);
		y += 4;
		i++;
	}
	EndScissorMode();
}

void	handle_chat_scroll(t_game *game)
{
	Rectangle	area;
	int			content_height;
	int			max_scroll;
	float		wheel;

	area = get_chat_messages_rect();
	if (!CheckCollisionPointRec(GetMousePosition(), area))
		return ;
	wheel = GetMouseWheelMove();
	if (wheel == 0)
		return ;
	content_height = get_chat_content_height(game, area.width);
	max_scroll = content_height - area.height;
	if (max_scroll < 0)
		max_scroll = 0;
	game->chat_scroll += wheel * 25;
	if (game->chat_scroll < 0)
		game->chat_scroll = 0;
	if (game->chat_scroll > max_scroll)
		game->chat_scroll = max_scroll;
	game->chat_auto_scroll = game->chat_scroll == 0;
}
