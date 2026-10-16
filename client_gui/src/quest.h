#ifndef QUEST_H
# define QUEST_H

#include "game.h"

int	parse_quest(const char *response, t_game *game);
void quest_state(t_game *game, char *buf);

#endif
