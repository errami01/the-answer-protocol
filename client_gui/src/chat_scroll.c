/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chat_scroll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 17:37:43 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 17:49:52 by msturma          ###   ########.fr       */
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
		height += draw_chat_message(game->chat[i],
			0, 0, width, false);
		height += 4;
		i++;
	}
	return (height);
}

static void	draw_chat_messages(t_game *game)
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
	y = area.y + area.height - content_height + game->chat_scroll;
	BeginScissorMode((int)area.x, (int)area.y, (int)area.width, (int)area.height);
	i = 0;
	while (i < game->chat_count)
	{
		y += draw_chat_message(game->chat[i], area.x, y, area.width, true);
		y += 4;
		i++;
	}
	EndScissorMode();
}
