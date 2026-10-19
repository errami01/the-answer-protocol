#include "login.h"

static void	draw_input(t_login *login, int screen_width, int screen_height)
{
	int	input_x;
	int	input_y;

	input_x = (screen_width - INPUT_WIDTH) / 2;
	input_y = (screen_height - INPUT_HEIGHT) / 2 - 30;
	DrawRectangleLines(input_x, input_y, INPUT_WIDTH, INPUT_HEIGHT, DARKGRAY);
	DrawText(login->username, input_x + 10, input_y + 10, 20, BLACK);
}

static Rectangle	get_button(int screen_width, int screen_height)
{
	int			button_x;
	int			button_y;
	Rectangle	button;

	button_x = (screen_width - BUTTON_WIDTH) / 2;
	button_y = ((screen_height - INPUT_HEIGHT) / 2 - 30)
		+ INPUT_HEIGHT + SPACING;
	button = (Rectangle){
		button_x,
		button_y,
		BUTTON_WIDTH,
		BUTTON_HEIGHT
	};
	return (button);
}

static void	draw_button(Rectangle button, Vector2 mouse)
{
	char	*button_text;
	int		text_width;
	Color	button_color;

	button_text = "Submit";
	text_width = MeasureText(button_text, 20);
	if (CheckCollisionPointRec(mouse, button))
		button_color = LIGHTGRAY;
	else
		button_color = GRAY;
	DrawRectangleRec(button, button_color);
	DrawText(button_text, (int)button.x + (BUTTON_WIDTH - text_width) / 2,
		(int)button.y + (BUTTON_HEIGHT - 20) / 2,
		20, BLACK);
}

void	login_draw(t_scene *scene)
{
	t_login		*login;
	int			screen_width;
	int			screen_height;
	Rectangle	button;
	Vector2		mouse;

	login = (t_login *)scene;
	screen_width = GetScreenWidth();
	screen_height = GetScreenHeight();
	draw_input(login, screen_width, screen_height);
	button = get_button(screen_width, screen_height);
	mouse = GetMousePosition();
	ClearBackground(RAYWHITE);
	draw_button(button, mouse);
}
