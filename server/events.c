/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 14:43:52 by aberrami          #+#    #+#             */
/*   Updated: 2026/11/07 11:54:07 by aberrami         ###   ########.fr       */
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

static int	count_room_players(t_world *w, t_room *room)
{
	int		i;
	int		total;

	i = 0;
	total = 0;
	while (i < MAX_CLIENTS)
	{
		if (w->players[i].fd != -1
			&& w->players[i].current_room == room)
			total++;
		i++;
	}
	return (total);
}

static void	write_msg(t_world *world, t_room *room, int i)
{
	char	out[256];

	snprintf(out, sizeof(out),
		"EVT STATS players={\"server\": %d, \"room\": %d}\n",
		count_total_players(world), count_room_players(world, room));
	write(world->players[i].fd, out, strlen(out));
}

void	broadcast_stats(t_world *world, t_room *new_room, t_room *old_room,
			int in_or_out)
{
	int		i;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (world->players[i].fd != -1)
		{
			if (world->players[i].current_room != new_room
				&& world->players[i].current_room != old_room && in_or_out)
				write_msg(world, world->players[i].current_room, i);
			else if (world->players[i].current_room == new_room
				&& new_room != NULL)
				write_msg(world, new_room, i);
			else if (world->players[i].current_room == old_room
				&& old_room != NULL)
				write_msg(world, old_room, i);
		}
		i++;
	}
}
