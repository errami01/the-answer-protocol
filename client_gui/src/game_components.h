#ifndef GAME_COMPONENTS_H
# define GAME_COMPONENTS_H

#define LIST_WIDTH 180
#define LIST_HEIGHT 32
#define LIST_SPACING 8
#define LIST_MARGIN 20

#include <raylib.h>
#include "game.h"

void draw_items(t_game *game);
void draw_npcs(t_game *game);

#endif
