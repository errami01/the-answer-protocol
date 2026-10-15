#ifndef GAME_COMMANDS_H
# define GAME_COMMANDS_H

#include "game.h"

void move(t_game *game, const char *direction);
void take(t_game *game, const char *item);
void inventory(t_game *game);
void quests(t_game *game);
void status(t_game *game);

#endif
