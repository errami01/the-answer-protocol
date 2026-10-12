#ifndef NPC_H
# define NPC_H

#include "game.h"
#include <raylib.h>

typedef enum e_dialog_state {
    NPC_WAIT_ACTION,
    NPC_WAIT_TALK,
    NPC_WAIT_QUEST,
    NPC_WAIT_ATTACK
} t_dialog_state;

void draw_npc_dialog(t_game *game);
void handle_npc_dialog(t_game *game);
void talk(t_game *game, const char *npc);
void quest(t_game *game, const char *npc);
void attack(t_game *game, const char *npc);
int parse_quest(const char *response, t_game *game);

#endif
