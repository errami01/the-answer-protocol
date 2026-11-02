/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chat_draw_messages.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 08:36:46 by msturma           #+#    #+#             */
/*   Updated: 2026/11/02 08:41:54 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chat.h"
#include <raylib.h>

static int	get_chat_scroll_y(t_game *game, Rectangle area)
{
	int	content_height;
	int	max_scroll;

	content_height = get_chat_content_height(game, area.width);
	max_scroll = content_height - area.height;
	if (max_scroll < 0)
		max_scroll = 0;
	if (game->chat_auto_scroll)
		game->chat_scroll = 0;
	if (game->chat_scroll > max_scroll)
		game->chat_scroll = max_scroll;
	return ((int)area.y - max_scroll + (int)game->chat_scroll);
}

static void	draw_chat_message_list(t_game *game, Rectangle area, int y)
{
	int	i;

	i = 0;
	while (i < game->chat_count)
	{
		y += draw_chat_message(game->chat[i],
				(Vector2){area.x, y}, area.width, true);
		y += 4;
		i++;
	}
}

void	draw_chat_messages(t_game *game)
{
	Rectangle	area;
	int			y;

	area = get_chat_messages_rect();
	y = get_chat_scroll_y(game, area);
	BeginScissorMode((int)area.x, (int)area.y,
		(int)area.width, (int)area.height);
	draw_chat_message_list(game, area, y);
	EndScissorMode();
}
