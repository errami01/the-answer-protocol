/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_arrow_buttons.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 15:24:50 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:18:38 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_arrow_buttons.h"
#include <raylib.h>

Rectangle	get_north_button(void)
{
	int			cx;
	int			cy;
	Rectangle	x;

	cx = GetScreenWidth() / 2;
	cy = GetScreenHeight() / 2;
	x = (Rectangle){cx - 60, cy - 140, 120, 60};
	return (x);
}

Rectangle	get_south_button(void)
{
	int			cx;
	int			cy;
	Rectangle	x;

	cx = GetScreenWidth() / 2;
	cy = GetScreenHeight() / 2;
	x = (Rectangle){cx - 60, cy + 80, 120, 60};
	return (x);
}

Rectangle	get_west_button(void)
{
	int			cx;
	int			cy;
	Rectangle	x;

	cx = GetScreenWidth() / 2;
	cy = GetScreenHeight() / 2;
	x = (Rectangle){cx - 220, cy - 30, 120, 60};
	return (x);
}

Rectangle	get_east_button(void)
{
	int			cx;
	int			cy;
	Rectangle	x;

	cx = GetScreenWidth() / 2;
	cy = GetScreenHeight() / 2;
	x = (Rectangle){cx + 100, cy - 30, 120, 60};
	return (x);
}
