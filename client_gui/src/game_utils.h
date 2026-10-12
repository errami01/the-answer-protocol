#ifndef GAME_UTILS_H
# define GAME_UTILS_H

#include "game.h"

int parse_look(const char *response, t_room *room);
int extract_json_string(const char *json, const char *key, char *dst, size_t dst_size);

#endif
