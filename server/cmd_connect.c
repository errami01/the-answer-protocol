/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_connect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:43:23 by aberrami          #+#    #+#             */
/*   Updated: 2026/10/04 14:59:28 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

int cmd_connect(struct pollfd *fds, int i, char *buf, t_world *world)
{
	if (is_name_taken(buf + 8, world->players, fds[i].fd))
		return (1);
	init_player(&world->players[i], fds[i].fd, buf + 8, world->rooms);
	return (1);
}

int	cmd_quit(struct pollfd *fds, int i, t_world *world)
{
	write(fds[i].fd, "OK bye\n", 7);
	handle_disconnect(world, i, fds);
	return (1);
}
