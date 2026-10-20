/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quests_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:22:12 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:22:16 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quests.h"
#include "game.h"

static Rectangle	get_quests_panel(void)
{
	int	width;
	int	height;

	width = 500;
	height = 400;
	return ((Rectangle){
		(GetScreenWidth() - width) / 2,
		(GetScreenHeight() - height) / 2,
		width,
		height
	});
}

static void	draw_quests_panel(Rectangle panel)
{
	char	*title;

	title = "Quests";
	DrawRectangle(0, 0, GetScreenWidth(),
		GetScreenHeight(), Fade(BLACK, 0.55f));
	DrawRectangleRec(panel, RAYWHITE);
	DrawRectangleLinesEx(panel, 2, DARKGRAY);
	DrawText(title,
		panel.x + (panel.width - MeasureText(title, 28)) / 2,
		panel.y + 20, 28, BLACK);
}

static void	draw_quest_item(t_quest *quest, Rectangle panel, int index)
{
	Rectangle	rect;

	rect = (Rectangle){
		panel.x + 30,
		panel.y + 80 + index * 60,
		panel.width - 60,
		50
	};
	DrawRectangleRec(rect, LIGHTGRAY);
	DrawRectangleLinesEx(rect, 1, DARKGRAY);
	DrawText(quest->id, rect.x + 10, rect.y + 7, 18, BLACK);
	DrawText(TextFormat("Status: %s", quest->status),
		rect.x + 10, rect.y + 28, 14, DARKGRAY);
}

void	draw_quests(t_game *game)
{
	Rectangle	panel;
	int			i;
	char		*text;

	panel = get_quests_panel();
	draw_quests_panel(panel);
	if (game->quest_count == 0)
	{
		text = "No active quests";
		DrawText(text,
			panel.x + (panel.width - MeasureText(text, 18)) / 2,
			panel.y + 100, 18, GRAY);
		return ;
	}
	i = 0;
	while (i < game->quest_count)
	{
		draw_quest_item(&game->quests[i], panel, i);
		i++;
	}
}
