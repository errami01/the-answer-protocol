/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 22:11:24 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/30 12:28:05 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"
#include <string.h>
#include <stdlib.h>

int	validate_player_name(const char *name, const t_player *players, int fd)
{
	int	i;

	i = 0;
	// return (1);
	while (i < MAX_CLIENTS)
	{
		if (players[i].name && strcmp(players[i].name, name) == 0)
		{
			write(fd, "ERR 201 NAME_IN_USE\n", 20);
			return (0);
		}
		i++;
	}
	return (1);
}

void	init_player(t_player *player, int fd, char *name, t_room *start_room)
{
	player->fd = fd;
	player->name = strdup(name);
	player->current_room = start_room;
	player->hp = 100;
	player->inventory = NULL;
}

t_player	*get_player_by_fd(t_world *world, int fd)
{
	int	i;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (world->players[i].fd == fd)
			return (&world->players[i]);
		i++;
	}
	return (NULL);
}
