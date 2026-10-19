#include "hp.h"
#include "json_parser.h"
#include <raylib.h>

int	parse_status(char *response, t_game *game)
{
	if (extract_int(response, "\"hp\"", &game->hp) < 0
		|| extract_int(response, "\"max_hp\"", &game->max_hp) < 0)
		return (-1);
	return (0);
}

void	draw_hp_bar(t_game *game)
{
	int		x;
	int		y;
	float	ratio;
	int		filled_width;
	char	text[64];

	x = MARGIN;
	y = GetScreenHeight() - BAR_HEIGHT - MARGIN;
	if (game->max_hp <= 0)
		ratio = 0.0f;
	else
		ratio = (float)game->hp / (float)game->max_hp;
	if (ratio < 0.0f)
		ratio = 0.0f;
	if (ratio > 1.0f)
		ratio = 1.0f;
	filled_width = (int)(BAR_WIDTH * ratio);
	DrawRectangle(x, y, BAR_WIDTH, BAR_HEIGHT, DARKGRAY);
	DrawRectangle(x, y, filled_width, BAR_HEIGHT, RED);
	DrawRectangleLines(x, y, BAR_WIDTH, BAR_HEIGHT, BLACK);
	snprintf(text, sizeof(text), "%d / %d HP", game->hp, game->max_hp);
	DrawText(text, x + 8, y + 4, 16, WHITE);
}
