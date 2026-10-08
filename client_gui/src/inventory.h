#ifndef INVENTORY_H
# define INVENTORY_H

#include "game.h"

void draw_inventory(char **items);
int parse_inventory(const char *response, t_game *game);
void clear_inventory(t_game *game);

#endif
