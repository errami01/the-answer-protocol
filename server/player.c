/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 22:11:24 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/22 20:51:01 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mud.h"
#include <string.h>
#include <stdlib.h>

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