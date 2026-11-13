/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_invite_draw.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:37:27 by msturma           #+#    #+#             */
/*   Updated: 2026/11/13 14:37:28 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "group.h"

Rectangle	get_invite_panel(void)
{
	return ((Rectangle){
		GetScreenWidth() - INVITE_MARGIN
		- INVITE_RIGHT_WIDTH - INVITE_GAP - INVITE_WIDTH,
		20,
		INVITE_WIDTH,
		INVITE_HEIGHT
	});
}

Rectangle	get_accept_button(Rectangle panel)
{
	return ((Rectangle){
		panel.x + 55,
		panel.y + 70,
		42,
		32
	});
}

Rectangle	get_decline_button(Rectangle panel)
{
	return ((Rectangle){
		panel.x + 123,
		panel.y + 70,
		42,
		32
	});
}

void	draw_group_invite(t_game *game)
{
	Rectangle	panel;
	Rectangle	accept;
	Rectangle	decline;
	char		text[MAX_PLAYER_NAME + 16];

	if (!game->group_invite_open)
		return ;
	panel = get_invite_panel();
	accept = get_accept_button(panel);
	decline = get_decline_button(panel);
	DrawRectangleRounded(panel, 0.1f, 8, RAYWHITE);
	DrawRectangleLinesEx(panel, 2, DARKGRAY);
	DrawText("Group Invite", panel.x + (panel.width
			- MeasureText("Group Invite", 20)) / 2, panel.y + 10, 20, BLACK);
	snprintf(text, sizeof(text), "From: %s", game->group_invite_sender);
	DrawText(text, panel.x + (panel.width
			- MeasureText(text, 16)) / 2, panel.y + 40, 16, DARKGRAY);
	DrawRectangleRounded(accept, 0.2f, 6, GREEN);
	DrawRectangleRounded(decline, 0.2f, 6, RED);
	draw_accept_icon(accept);
	draw_decline_icon(decline);
}
