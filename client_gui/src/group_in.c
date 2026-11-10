#include "game.h"
#include "group.h"
#include "notification.h"

static Rectangle	get_leave_button(Rectangle panel)
{
	return ((Rectangle){
		panel.x + (panel.width - 190) / 2,
		(panel.y + (panel.height - 122) / 2) + 84,
		190,
		38
	});
}

void	draw_in_group(t_game *game, Rectangle panel)
{
	Rectangle	leave;
	Vector2		mouse;
	char		text[64];

	leave = get_leave_button(panel);
	mouse = GetMousePosition();
	snprintf(text, sizeof(text), "%s's group", game->group_leader);
	DrawText(text, (GetScreenWidth()
			- MeasureText(text, 18)) / 2,
		panel.y + (panel.height - 122) / 2, 18, DARKGRAY);
	draw_group_input(game, panel);
	if (CheckCollisionPointRec(mouse, leave))
		DrawRectangleRec(leave, DARKGRAY);
	else
		DrawRectangleRec(leave, LIGHTGRAY);
	DrawText("Leave",
		leave.x + (leave.width - MeasureText("Leave", 18)) / 2,
		leave.y + (leave.height - 18) / 2,
		18, BLACK);
}

void	handle_group_leave(t_game *game)
{
	Rectangle	panel;
	Rectangle	leave;
	Vector2		mouse;

	if (!game->group_window_open || !IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		return ;
	if (!game->group_joined)
		return ;
	panel = get_group_window_panel();
	leave = get_leave_button(panel);
	mouse = GetMousePosition();
	if (CheckCollisionPointRec(mouse, leave))
	{
		client_send(game->manager->client, "GROUP LEAVE\n");
		game->state = GAME_WAIT_GROUP_LEAVE;
	}
}

void	wait_group_leave(t_game *game, char *buf)
{
	if (game->state != GAME_WAIT_GROUP_LEAVE)
		return ;
	if (strncmp(buf, "OK", 2) == 0)
	{
		game->group_joined = 0;
		game->group_leader[0] = '\0';
		game->state = GAME_IDLE;
		return ;
	}
	show_notification(game, "Error while leaving a group.");
	game->state = GAME_IDLE;
}
