/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_arrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 15:26:59 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:18:49 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raylib.h"
#include "game_arrows.h"

void	draw_arrow_up(int x, int y, const char *room_name)
{
	int	width;

	DrawTriangle(
		(Vector2){x, y - 20},
		(Vector2){x - 15, y + 10},
		(Vector2){x + 15, y + 10},
		BLACK
		);
	width = MeasureText(room_name, 20);
	DrawText(
		room_name,
		x - width / 2,
		y + 20,
		20,
		BLACK
		);
}

void	draw_arrow_down(int x, int y, const char *room_name)
{
	int	width;

	DrawTriangle(
		(Vector2){x, y + 20},
		(Vector2){x + 15, y - 10},
		(Vector2){x - 15, y - 10},
		BLACK
		);
	width = MeasureText(room_name, 20);
	DrawText(
		room_name,
		x - width / 2,
		y - 40,
		20,
		BLACK
		);
}

void	draw_arrow_left(int x, int y, const char *room_name)
{
	int	width;

	DrawTriangle(
		(Vector2){x - 20, y},
		(Vector2){x + 10, y + 15},
		(Vector2){x + 10, y - 15},
		BLACK
		);
	width = MeasureText(room_name, 20);
	DrawText(
		room_name,
		x - width - 30,
		y - 10,
		20,
		BLACK
		);
}

void	draw_arrow_right(int x, int y, const char *room_name)
{
	DrawTriangle(
		(Vector2){x + 20, y},
		(Vector2){x - 10, y - 15},
		(Vector2){x - 10, y + 15},
		BLACK
		);
	DrawText(
		room_name,
		x + 30,
		y - 10,
		20,
		BLACK
		);
}
