#ifndef NOTIFICATION_H
# define NOTIFICATION_H

#include "game.h"

#define DURATION 5.0

void show_notification(t_game *game, const char *text);
void draw_notification(t_game *game);

#endif
