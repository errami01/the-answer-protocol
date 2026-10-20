/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:21:13 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:21:15 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "notification.h"

void	show_notification(t_game *game, const char *text)
{
	strncpy(game->notification, text, sizeof(game->notification) - 1);
	game->notification[sizeof(game->notification) - 1] = '\0';
	game->notification_time = GetTime();
}

static void	draw_notification_core(t_game *game, float alpha)
{
	int		text_width;
	int		font_size;
	Color	color;
	int		x;
	int		y;

	font_size = 20;
	text_width = MeasureText(game->notification, font_size);
	x = (GetScreenWidth() - text_width) / 2;
	y = GetScreenHeight() - 90;
	color = Fade(BLACK, alpha);
	DrawText(game->notification, x, y, font_size, color);
}

void	draw_notification(t_game *game)
{
	double	elapsed;
	float	alpha;
	int		x;
	int		y;

	if (game->notification[0] == '\0')
		return ;
	elapsed = GetTime() - game->notification_time;
	if (elapsed >= DURATION)
	{
		game->notification[0] = '\0';
		return ;
	}
	if (elapsed < 3.0)
		alpha = 1.0f;
	else
		alpha = (float)((DURATION - elapsed) / 2.0);
	draw_notification_core(game, alpha);
}
