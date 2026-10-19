#ifndef ATTACK_H
# define ATTACK_H

# include "game.h"

int		parse_attack_response(const char *response,
			int *attacker_hp, int *target_hp, int *damage);
void	attack_state(t_game *game, char *buf);

#endif
