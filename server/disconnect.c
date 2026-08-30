/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disconnect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 11:08:20 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/30 11:09:24 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mud.h"


void	handle_disconnect(t_world *world, int i, struct pollfd *fds)
{
	t_player	*p;
	char		msg[256];

	p = &world->players[i];
	if (p->fd != -1)
	{
		if (p->name && p->current_room)
		{
			snprintf(msg, sizeof(msg), "EVT ROOM PRESENCE LEAVE %s\n", p->name);
			broadcast_to_room(world, p->current_room, msg, p->fd);
			printf("Log: Player %s disconnected gracefully.\n", p->name);
		}
		if (p->name)
			free(p->name);
		close(p->fd);
	}
	/* Reset player slot for reuse */
	memset(p, 0, sizeof(t_player));
	p->fd = -1;
	/* Reset poll structure */
	fds[i].fd = -1;
	fds[i].events = 0;
	fds[i].revents = 0;
}