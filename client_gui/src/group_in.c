#include "group.h"

static Rectangle	get_leave_button(Rectangle panel)
{
	return ((Rectangle){
		panel.x + (panel.width - 190) / 2,
		panel.y + ((panel.height - 76) / 2) + 38,
		190,
		38
	});
}

void	draw_in_group(t_game *game, Rectangle panel)
{
	Rectangle	leave;
	char		text[64];

	leave = get_leave_button(panel);
	snprintf(text, sizeof(text), "%s's group", game->group_leader);
	DrawText(text, (GetScreenWidth()
			- MeasureText(text, 18)) / 2, panel.y + 60, 18, DARKGRAY);
	DrawRectangleRec(leave, LIGHTGRAY);
	DrawText("Leave",
		leave.x + (leave.width - MeasureText("Leave", 18)) / 2,
		leave.y + (leave.height - 18) / 2,
		18, BLACK);
}
