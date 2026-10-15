#ifndef HP_H
# define HP_H

#include "game.h"

void draw_hp_bar(t_game *game);
int parse_status(char *response, t_game *game);

#endif
