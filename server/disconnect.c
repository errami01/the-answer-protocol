/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disconnect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 11:08:20 by aberrami          #+#    #+#             */
/*   Updated: 2026/10/11 21:25:29 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

void	cleanup_client(struct pollfd *fds, int i)
{
	close(fds[i].fd);
	fds[i].fd = -1;
	fds[i].events = 0;
	fds[i].revents = 0;
}

void	clean_player(t_player *p)
{
	if (p->name)
		free(p->name);
	close(p->fd);
}

static void	log_discon(t_player *p, char *msg)
{
	char		*user;

	user = "Unknown";
	if (p->name)
		user = p->name;
	snprintf(msg, 100, "Player %s disconnected", user);
	msg[strlen(msg)-1] = '\0';
	printf("%s\n", msg);
	if (!p->name)
		user = "SYSTEM";
	log_event("INFO", user, msg, p->ip);
}

void	handle_disconnect(t_world *world, int i, struct pollfd *fds)
{
	t_player	*p;
	char		msg[256];

	p = &world->players[i];
	log_discon(p, msg);
	if (p->fd != -1)
	{
		if (p->name && p->current_room)
		{
			snprintf(msg, sizeof(msg), "EVT ROOM PRESENCE LEAVE %s\n", p->name);
			broadcast_to_room(world, p->current_room, msg, p->fd);
			msg[strlen(msg)-1] = '\0';
			log_event("INFO", p->name, msg, NULL);
		}
		clean_player(p);
	}
	memset(p, 0, sizeof(t_player));
	p->fd = -1;
	cleanup_client(fds, i);
}
