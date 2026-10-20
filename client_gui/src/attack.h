/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:17:58 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:18:00 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATTACK_H
# define ATTACK_H

# include "game.h"

int		parse_attack_response(const char *response,
			int *attacker_hp, int *target_hp, int *damage);
void	attack_state(t_game *game, char *buf);

#endif
