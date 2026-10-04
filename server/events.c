/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 14:43:52 by aberrami          #+#    #+#             */
/*   Updated: 2026/10/03 17:40:07 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"
#include <string.h>
#include <unistd.h>

void	broadcast_to_room(t_world *world, t_room *room,
		char *msg, int exclude_fd)
{
	int	i;

	if (!room || !msg)
		return ;
	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (world->players[i].fd != -1 && world->players[i].fd != exclude_fd)
		{
			if (world->players[i].current_room == room)
				write(world->players[i].fd, msg, strlen(msg));
		}
		i++;
	}
}

void	broadcast_global(t_world *world, char *msg, int exclude_fd)
{
	int	i;

	if (!msg)
		return ;
	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (world->players[i].fd != -1 && world->players[i].fd != exclude_fd)
			write(world->players[i].fd, msg, strlen(msg));
		i++;
	}
}
