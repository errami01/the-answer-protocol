#include "game.h"
#include "group.h"
#include <raylib.h>

static Rectangle	get_input_widget(Rectangle panel)
{
	return ((Rectangle){
		panel.x + (panel.width - 260) / 2,
		(panel.y + (panel.height - 122) / 2) + 32,
		260,
		38
	});
}

void	draw_group_input(t_game *game, Rectangle panel)
{
	Rectangle	input;
	Vector2		mouse;

	input = get_input_widget(panel);
	mouse = GetMousePosition();
	if (CheckCollisionPointRec(mouse, input))
		DrawRectangleLines(input.x, input.y, input.width, input.height, BLUE);
	else
		DrawRectangleLines(input.x, input.y, input.width,
			input.height, DARKGRAY);
	DrawText(game->group_invite_username, input.x + 10,
		input.y + (input.height - 18) / 2, 18, DARKGRAY);
}

void	handle_group_input_pointer(t_game *game)
{
	Rectangle	panel;
	Rectangle	input;
	Vector2		mouse;

	if (!game->group_window_open || !game->group_joined)
		return ;
	panel = get_group_window_panel();
	input = get_input_widget(panel);
	mouse = GetMousePosition();
	if (CheckCollisionPointRec(mouse, input) && game->state == GAME_IDLE)
	{
		game->state = GAME_WAIT_GROUP_INPUT;
		return ;
	}
	if (!CheckCollisionPointRec(mouse, input)
		&& game->state == GAME_WAIT_GROUP_INPUT)
	{
		game->state = GAME_IDLE;
		return ;
	}
}

void	handle_group_input(t_game *game)
{
	int			key;
	int			input_y;
	Rectangle	button;

	if (game->state != GAME_WAIT_GROUP_INPUT)
		return ;
	key = GetCharPressed();
	while (key > 0)
	{
		if (key >= 32 && key <= 126 && game->group_invite_username_len < 63)
		{
			game->group_invite_username[
				game->group_invite_username_len++] = (char)key;
			game->group_invite_username[game->group_invite_username_len] = '\0';
		}
		key = GetCharPressed();
	}
	if (IsKeyPressed(KEY_BACKSPACE) && game->group_invite_username_len > 0)
	{
		game->group_invite_username_len--;
		game->group_invite_username[game->group_invite_username_len] = '\0';
	}
}
