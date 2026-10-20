/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:17:55 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:17:56 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "attack.h"
#include "client.h"
#include "notification.h"
#include "json_parser.h"

int	parse_attack_response(const char *response, int *attacker_hp,
		int *target_hp, int *damage)
{
	if (extract_int(response, "\"attacker_hp\"", attacker_hp) < 0)
		return (-1);
	if (extract_int(response, "\"target_hp\"", target_hp) < 0)
		return (-1);
	if (extract_int(response, "\"damage\"", damage) < 0)
		return (-1);
	return (0);
}

void	attack_state(t_game *game, char *buf)
{
	int		attacker_hp;
	int		target_hp;
	int		damage;
	char	notification[256];

	if (parse_attack_response(buf, &attacker_hp, &target_hp, &damage) < 0)
	{
		show_notification(game, "Failed to attack.");
		return ;
	}
	game->hp = attacker_hp;
	snprintf(notification, sizeof(notification),
		"Dealt %d damage. Enemy HP: %d", damage, target_hp);
	show_notification(game, notification);
	if (target_hp <= 0)
	{
		if (client_send(game->manager->client, "LOOK\n") < 0)
			return ;
		game->state = GAME_WAIT_LOOK;
		return ;
	}
	game->state = GAME_IDLE;
}
