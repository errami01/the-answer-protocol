#ifndef GAME_H
# define GAME_H

#include "client.h"

#define MAX_INVENTORY 32

typedef struct s_room {
    char name[128];
    char description[128];

    char north[128];
    char west[128];
    char south[128];
    char east[128];

    char items[10][128];
    int item_count;

    char npcs[10][128];
    int npc_count;
} t_room;

typedef enum e_game_state {
    GAME_IDLE,
    GAME_WAIT_MOVE,
    GAME_WAIT_LOOK,
    GAME_WAIT_TAKE,
    GAME_WAIT_INVENTORY,
} t_game_state;

typedef struct s_game {
    t_scene base;
    t_manager *manager;
    t_room *current;
    t_game_state state;

    int inventory_open;
    char *inventory[MAX_INVENTORY];
} t_game;

t_scene *game_create(t_manager *manager, const char *look_init);

#endif
