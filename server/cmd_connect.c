/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_connect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:43:23 by aberrami          #+#    #+#             */
/*   Updated: 2026/10/25 10:43:27 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

static void	broad_player_presence(t_world *world, int i)
{
	char		msg[256];
	t_player	*p;

	p = &world->players[i];
	snprintf(msg, sizeof(msg), "EVT ROOM PRESENCE ENTER %s\n", p->name);
	broadcast_to_room(world, p->current_room, msg, p->fd);
	msg[strlen(msg)-1] = '\0';
	log_event("INFO", p->name, msg, NULL);
}

int	cmd_connect(struct pollfd *fds, int i, char *buf, t_world *world)
{
	if (is_name_taken(buf + 8, world->players, fds[i].fd))
		return (1);
	if (init_player(&world->players[i], fds[i].fd, buf + 8, world->rooms))
		broad_player_presence(world, i);
	return (1);
}

int	cmd_quit(struct pollfd *fds, int i, t_world *world)
{
	write(fds[i].fd, "OK bye\n", 7);
	handle_disconnect(world, i, fds);
	return (1);
}
