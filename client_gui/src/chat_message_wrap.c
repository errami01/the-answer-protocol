/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chat_message_wrap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 17:40:21 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 17:41:37 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chat.h"

int	draw_chat_message(const char *text, int x, int y, int max_width, bool draw)
{
	char	line[CHAT_MESSAGE_LEN];
	int		i;
	int		len;
	int		height;

	i = 0;
	len = 0;
	height = 0;
	while (text[i])
	{
		if (text[i] == '\n'
			|| (len > 0 && MeasureText(line, 14) > max_width))
		{
			line[len] = '\0';
			if (draw)
				DrawText(line, x, y + height, 14, BLACK);
			height += 18;
			len = 0;
			if (text[i] == '\n')
			{
				i++;
				continue ;
			}
		}
		if (len >= CHAT_MESSAGE_LEN - 1)
			break ;
		line[len++] = text[i++];
		line[len] = '\0';
	}
	if (len > 0)
	{
		if (draw)
			DrawText(line, x, y + height, 14, BLACK);
		height += 18;
	}
	return (height);
}
