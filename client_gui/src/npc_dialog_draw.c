/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_dialog_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:21:41 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:21:41 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "npc.h"

static void	draw_npc_action_button(Rectangle rect, const char *text)
{
	Vector2		mouse;
	Color		color;
	int			text_width;

	mouse = GetMousePosition();
	color = LIGHTGRAY;
	if (CheckCollisionPointRec(mouse, rect))
		color = GRAY;
	DrawRectangleRec(rect, color);
	DrawRectangleLinesEx(rect, 1, DARKGRAY);
	text_width = MeasureText(text, 18);
	DrawText(text, rect.x + (rect.width - text_width) / 2,
		rect.y + (rect.height - 18) / 2, 18, BLACK);
}

static void	draw_npc_close_button(Rectangle dialog)
{
	Rectangle	close_btn;
	Vector2		mouse;
	Color		color;

	mouse = GetMousePosition();
	close_btn = (Rectangle){
		dialog.x + dialog.width - 40,
		dialog.y + 10,
		30,
		30
	};
	if (CheckCollisionPointRec(mouse, close_btn))
		color = LIGHTGRAY;
	else
		color = RAYWHITE;
	DrawRectangleRec(close_btn, color);
	DrawText("X", close_btn.x + 8, close_btn.y + 4, 20, BLACK);
}

static void	draw_npc_actions(Rectangle dialog)
{
	Rectangle	button;

	button = (Rectangle){
		dialog.x + 30,
		dialog.y + 100,
		100,
		40
	};
	draw_npc_action_button(button, "Talk");
	button.x = dialog.x + 160;
	draw_npc_action_button(button, "Quest");
	button.x = dialog.x + 290;
	draw_npc_action_button(button, "Attack");
}

static void	draw_text_field(t_game *game, Rectangle dialog)
{
	Rectangle	text_field;

	text_field = (Rectangle){
		dialog.x + 30,
		dialog.y + 170,
		dialog.width - 60,
		90
	};
	if (game->npc_response[0] != '\0')
	{
		draw_text_wrapped(game->npc_response,
			(Rectangle){
			text_field.x + 10,
			text_field.y + 10,
			text_field.width - 20,
			text_field.height - 20},
			18, BLACK);
	}
}

void	draw_npc_dialog(t_game *game)
{
	Rectangle	dialog;

	dialog = get_npc_dialog();
	DrawRectangle(0, 0, GetScreenWidth(),
		GetScreenHeight(), Fade(BLACK, 0.55f));
	DrawRectangleRec(dialog, RAYWHITE);
	DrawRectangleLinesEx(dialog, 2, DARKGRAY);
	DrawText(game->selected_npc, dialog.x + 20, dialog.y + 20, 24, BLACK);
	draw_npc_close_button(dialog);
	draw_npc_actions(dialog);
	draw_text_field(game, dialog);
}
