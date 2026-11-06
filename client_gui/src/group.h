#ifndef GROUP_H
# define GROUP_H

# include "game.h"

# define INVITE_WIDTH 220
# define INVITE_HEIGHT 115
# define INVITE_RIGHT_WIDTH 180
# define INVITE_GAP 12
# define INVITE_MARGIN 20

void		group_invite_receive(t_game *game, char *buf);
void		draw_accept_icon(Rectangle button);
void		draw_decline_icon(Rectangle button);
void		draw_group_invite(t_game *game);
void		handle_group_invite(t_game *game);
void		wait_invite_accept(t_game *game, char *buf);
Rectangle	get_invite_panel(void);
Rectangle	get_accept_button(Rectangle panel);
Rectangle	get_decline_button(Rectangle panel);

#endif
