#ifndef GROUP_H
# define GROUP_H

# include "game.h"

# define INVITE_WIDTH 220
# define INVITE_HEIGHT 115
# define INVITE_RIGHT_WIDTH 180
# define INVITE_GAP 12
# define INVITE_MARGIN 20

# define GROUP_WINDOW_WIDTH 420
# define GROUP_WINDOW_HEIGHT 260

void		group_invite_receive(t_game *game, char *buf);
void		draw_accept_icon(Rectangle button);
void		draw_decline_icon(Rectangle button);
void		draw_group_invite(t_game *game);
void		draw_group_window(t_game *game);
void		draw_in_group(t_game *game, Rectangle panel);
void		draw_not_in_group(t_game *game, Rectangle panel);
void		handle_group_invite(t_game *game);
void		wait_invite_accept(t_game *game, char *buf);
void		init_group_window(t_game *game);
void		handle_group_window(t_game *game);
void		handle_group_create(t_game *game);
Rectangle	get_invite_panel(void);
Rectangle	get_accept_button(Rectangle panel);
Rectangle	get_decline_button(Rectangle panel);
void		wait_group_create(t_game *game, char *buf);
void		handle_group_actions(t_game *game);

Rectangle	get_group_window_panel(void);
Rectangle	get_group_create_button(Rectangle panel);
Rectangle	get_group_invite_button(Rectangle panel);

#endif
