#include "players.h"

static Rectangle	get_players_panel(void)
{
	return ((Rectangle){
		(GetScreenWidth() - 360) / 2,
		(GetScreenHeight() - 340) / 2,
		360,
		340
	});
}

static void	draw_players_panel(t_game *game, Rectangle panel)
{
	char	text[128];

	DrawRectangle(0, 0, GetScreenWidth(),
		GetScreenHeight(), Fade(BLACK, 0.55f));
	DrawRectangleRec(panel, RAYWHITE);
	DrawRectangleLinesEx(panel, 2, DARKGRAY);
	snprintf(text, sizeof(text),
		"Online players: %d", game->server_player_count);
	DrawText(text, panel.x + (panel.width - MeasureText(text, 24)) / 2,
		panel.y + 20, 24, DARKGRAY);
	snprintf(text, sizeof(text), "Players in room:");
	DrawText(text, panel.x + (panel.width - MeasureText(text, 18)) / 2,
		panel.y + 65, 18, BLACK);
}

static void	draw_room_players(t_game *game, Rectangle panel)
{
	int	i;
	int	y;

	i = 0;
	y = panel.y + 100;
	BeginScissorMode((int)panel.x + 20, (int)y, (int)panel.width - 40, 155);
	while (i < game->room_player_count)
	{
		DrawText(game->room_players[i],
			panel.x + (panel.width
				- MeasureText(game->room_players[i], 18)) / 2,
			y + i * 26, 18, BLACK);
		i++;
	}
	EndScissorMode();
}

void	draw_players(t_game *game)
{
	Rectangle	panel;
	int			x;

	panel = get_players_panel();
	draw_players_panel(game, panel);
	draw_room_players(game, panel);
}
