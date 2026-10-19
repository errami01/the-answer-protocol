#include <raylib.h>
#include "inventory.h"
#include "game.h"

static void	init_panel(int *panel, int *panel_pos)
{
	panel[0] = 400;
	panel[1] = 350;
	panel_pos[0] = (panel[0] - 400) / 2;
	panel_pos[1] = (panel[1] - 350) / 2;
}

static void	inventory_label(int *panel, int *panel_pos, char **items)
{
	DrawText("Inventory",
		panel_pos[0] + (panel[0] - MeasureText("Inventory", 28)) / 2,
		panel_pos[1] + 20, 28, BLACK);
	if (items == NULL || items[0] == NULL)
	{
		DrawText("Inventory is empty",
			panel_pos[0] + (panel[0]
				- MeasureText("Inventory is empty", 18)) / 2,
			panel_pos[1] + 100, 18, GRAY);
		return ;
	}
}

void	draw_inventory(char **items)
{
	int	screen_width;
	int	screen_height;
	int	panel[2];
	int	panel_pos[2];
	int	i;

	screen_width = GetScreenWidth();
	screen_height = GetScreenHeight();
	DrawRectangle(0, 0, screen_width, screen_height, Fade(BLACK, 0.55f));
	init_panel(panel, panel_pos);
	DrawRectangle(panel_pos[0], panel_pos[1], panel[0], panel[1], RAYWHITE);
	DrawRectangleLinesEx((Rectangle){panel_pos[0], panel_pos[1],
		panel[0], panel[1]}, 2, DARKGRAY);
	inventory_label(panel, panel_pos, items);
	i = 0;
	while (items[i] != NULL)
	{
		DrawText(items[i], panel_pos[0] + 30,
			panel_pos[1] + 80 + i * 30, 20, BLACK);
		i++;
	}
}

void	clear_inventory(t_game *game)
{
	int	i;

	i = 0;
	while (i < MAX_INVENTORY && game->inventory[i] != NULL)
	{
		free(game->inventory[i]);
		game->inventory[i] = NULL;
		i++;
	}
}
