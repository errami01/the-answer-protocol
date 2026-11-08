#include "game.h"
#include "group.h"
#include "notification.h"

static void	draw_not_in_content(Rectangle panel, Rectangle create, char *text)
{
	int	content_height;
	int	start_y;

	content_height = create.height + 38;
	start_y = panel.y + (panel.height - content_height) / 2;
	DrawText(text, panel.x + (panel.width
			- MeasureText(text, 18)) / 2, start_y, 18, DARKGRAY);
	DrawRectangleRec(create, LIGHTGRAY);
	DrawText("Create", create.x + (create.width
			- MeasureText("Create", 18)) / 2,
		create.y + (create.height - 18) / 2, 18, BLACK);
}

void	draw_not_in_group(t_game *game, Rectangle panel)
{
	Rectangle	create;
	char		*text;

	text = "You're not in any group yet";
	create = get_group_create_button(panel);
	draw_not_in_content(panel, create, text);
}

void	handle_group_create(t_game *game)
{
	Rectangle	panel;
	Rectangle	create;
	Vector2		mouse;

	if (!game->group_window_open || !IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		return ;
	panel = get_group_window_panel();
	create = get_group_create_button(panel);
	mouse = GetMousePosition();
	if (CheckCollisionPointRec(mouse, create))
	{
		client_send(game->manager->client, "GROUP CREATE\n");
		game->state = GAME_WAIT_GROUP_CREATE;
	}
}

void	wait_group_create(t_game *game, char *buf)
{
	if (game->state != GAME_WAIT_GROUP_CREATE)
		return ;
	if (strncmp(buf, "OK", 2) == 0)
	{
		game->group_joined = 1;
		strcpy(game->group_leader, buf + 9);
		game->group_leader[strlen(game->group_leader) - 1] = '\0';
		game->state = GAME_IDLE;
		return ;
	}
	show_notification(game, "Failed to create a group");
	game->state = GAME_IDLE;
}
