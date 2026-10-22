/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chat_message_wrap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 17:40:21 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 19:09:44 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chat.h"

static void	draw_chat_line(t_chat_text *chat)
{
	chat->line[chat->len] = '\0';
	if (chat->draw)
		DrawText(chat->line, chat->pos.x,
			chat->pos.y + chat->height, 14, BLACK);
	chat->height += 18;
	chat->len = 0;
}

static void	process_chat_char(t_chat_text *chat, char c)
{
	if (c == '\n')
	{
		draw_chat_line(chat);
		return ;
	}
	chat->line[chat->len] = c;
	chat->line[chat->len + 1] = '\0';
	if (chat->len > 0
		&& MeasureText(chat->line, 14) > chat->max_width)
	{
		chat->line[chat->len] = '\0';
		draw_chat_line(chat);
		chat->line[0] = c;
		chat->line[1] = '\0';
		chat->len = 1;
		return ;
	}
	chat->len++;
}

int	draw_chat_message(const char *text, Vector2 pos,
		int max_width, bool draw)
{
	t_chat_text	chat;
	int			i;

	if (!text)
		return (0);
	chat = (t_chat_text){
		.len = 0,
		.height = 0,
		.max_width = max_width,
		.pos = pos,
		.draw = draw
	};
	i = 0;
	while (text[i])
	{
		if (chat.len >= 254)
			draw_chat_line(&chat);
		process_chat_char(&chat, text[i]);
		i++;
	}
	if (chat.len > 0)
		draw_chat_line(&chat);
	return (chat.height);
}
