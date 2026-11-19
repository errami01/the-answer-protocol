/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 17:38:16 by aberrami          #+#    #+#             */
/*   Updated: 2026/11/18 15:57:36 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

t_player	*find_player_by_name(t_world *w, char *name)
{
	int	i;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (w->players[i].fd != -1 && w->players[i].name
			&& strcmp(w->players[i].name, name) == 0)
			return (&w->players[i]);
		i++;
	}
	return (NULL);
}

int	is_target_in_group(t_player *target, t_player *grp_leader)
{
	if (target->group_id && strcmp(target->group_id, grp_leader->name) == 0)
	{
		write(grp_leader->fd, "ERR 402 ALREADY_IN_GROUP\n", 25);
		log_event("WARN", grp_leader->name, "ERR 402 ALREADY_IN_GROUP", NULL);
		return (1);
	}
	return (0);
}

void	broadcast_group(t_world *w, char *gid, char *msg, int exclude_fd)
{
	int	i;

	if (!gid || !msg)
		return ;
	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (w->players[i].fd != -1 && w->players[i].fd != exclude_fd
			&& w->players[i].group_id
			&& strcmp(w->players[i].group_id, gid) == 0)
			write(w->players[i].fd, msg, strlen(msg));
		i++;
	}
}
