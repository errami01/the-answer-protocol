/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 14:46:34 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/30 22:46:22 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mud.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	get_dir_index(const char *dir)
{
	if (!dir) return (-1);
	if (strncmp(dir, "north", 5) == 0) return (0);
	if (strncmp(dir, "south", 5) == 0) return (1);
	if (strncmp(dir, "east", 4) == 0)  return (2);
	if (strncmp(dir, "west", 4) == 0)  return (3);
	return (-1);
}

void	cmd_move(t_player *p, char *arg, t_world *world)
{
	int		idx;
	t_room	*old_rm;
	char	msg[256];

	idx = get_dir_index(arg);
    
	if (idx == -1 || !p->current_room->exits[idx])
	{
		write(p->fd, "ERR 301 NO_EXIT\n", 16);
		return ;
	}
	old_rm = p->current_room;
	snprintf(msg, 256, "EVT ROOM PRESENCE LEAVE %s\n", p->name);
	broadcast_to_room(world, old_rm, msg, p->fd);
	p->current_room = old_rm->exits[idx];
	snprintf(msg, 256, "EVT ROOM PRESENCE ENTER %s\n", p->name);
	broadcast_to_room(world, p->current_room, msg, p->fd);
	snprintf(msg, 256, "OK room=%s\n", p->current_room->id);
	write(p->fd, msg, strlen(msg));
	msg[strlen(msg) -1] = '\0';
	log_event("INFO", p->name, msg);
}