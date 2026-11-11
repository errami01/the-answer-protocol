#include "group.h"

Rectangle	get_group_window_panel(void)
{
	return ((Rectangle){
		(GetScreenWidth() - GROUP_WINDOW_WIDTH) / 2,
		(GetScreenHeight() - GROUP_WINDOW_HEIGHT) / 2,
		GROUP_WINDOW_WIDTH,
		GROUP_WINDOW_HEIGHT
	});
}

Rectangle	get_group_create_button(Rectangle panel)
{
	return ((Rectangle){
		panel.x + (panel.width - 190) / 2,
		panel.y + ((panel.height - 76) / 2) + 38,
		190,
		38
	});
}

Rectangle	get_group_invite_button(Rectangle panel)
{
	return ((Rectangle){
		panel.x + (panel.width - 190) / 2,
		panel.y + 110,
		190,
		38
	});
}

Rectangle	get_input_widget(Rectangle panel)
{
	return ((Rectangle){
		panel.x + (panel.width - 330) / 2,
		(panel.y + (panel.height - 122) / 2) + 32,
		260,
		38
	});
}

Rectangle	get_input_button(Rectangle panel)
{
	Rectangle	input;

	input = get_input_widget(panel);
	return ((Rectangle){
		input.x + input.width + 8,
		input.y,
		62,
		input.height
	});
}
