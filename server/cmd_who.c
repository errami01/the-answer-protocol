/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_who.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 15:48:10 by aberrami          #+#    #+#             */
/*   Updated: 2026/10/24 15:48:15 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
** Builds the JSON list of players in the same room.
*/
static void	build_room_list(t_player *p, t_world *w, char *out)
{
	int		i;
	int		first;

	strlcat(out, "\"room\": [", 1024);
	i = 0;
	first = 1;
	while (i < MAX_CLIENTS)
	{
		if (w->players[i].fd != -1 && w->players[i].current_room == p->current_room)
		{
			if (!first)
				strlcat(out, ", ", 1024);
			strlcat(out, "\"", 1024);
			strlcat(out, w->players[i].name, 1024);
			strlcat(out, "\"", 1024);
			first = 0;
		}
		i++;
	}
	strlcat(out, "]", 1024);
}

void	cmd_who(t_player *p, t_world *w)
{
	char	out[1024];
	int		total;
	int		i;

	memset(out, 0, 1024);
	strlcpy(out, "OK { ", 1024);
	build_room_list(p, w, out);
	
	total = 0;
	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (w->players[i].fd != -1)
			total++;
		i++;
	}
	snprintf(out + strlen(out), 1024 - strlen(out), ", \"server\": %d }\n", total);
	write(p->fd, out, strlen(out));
}