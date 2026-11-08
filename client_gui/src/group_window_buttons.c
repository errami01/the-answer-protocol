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
