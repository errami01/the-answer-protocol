#ifndef PLAYERS_H
# define PLAYERS_H

# include "game.h"

void	players(t_game *game);
void	draw_players(t_game *game);
void	wait_who(t_game *game, char *buf);

void	add_player(t_game *game, const char *name);
void	remove_player(t_game *game, const char *name);

#endif
