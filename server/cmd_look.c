/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_look.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 22:13:46 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/21 22:13:56 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mud.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
** Formats the exits part of the JSON.
*/
static void	format_exits(t_room *r, char *buf, size_t size)
{
	const char	*dirs[] = {"north", "south", "east", "west", "up", "down"};
	int			i;
	int			first;

	strlcat(buf, "\"exits\": {", size);
	i = 0;
	first = 1;
	while (i < 6)
	{
		if (r->exits[i])
		{
			if (!first)
				strlcat(buf, ", ", size);
			strlcat(buf, "\"", size);
			strlcat(buf, dirs[i], size);
			strlcat(buf, "\": \"", size);
			strlcat(buf, r->exits[i]->id, size);
			strlcat(buf, "\"", size);
			first = 0;
		}
		i++;
	}
	strlcat(buf, "}", size);
}

/*
** Builds the full JSON response for LOOK (RFC 5.1.2).
*/
void	cmd_look(t_player *p)
{
	char	out[2048];
	t_room	*r;

	r = p->current_room;
	memset(out, 0, 2048);
	strlcpy(out, "OK { \"room\": { ", 2048);
	snprintf(out + strlen(out), 2048 - strlen(out), 
		"\"id\": \"%s\", \"name\": \"%s\", \"description\": \"%s\", ",
		r->id, r->name, r->description);
	format_exits(r, out, 2048);
	strlcat(out, " }, \"players\": [", 2048);
	/* Logic for other players in room goes here later */
	strlcat(out, "], \"items\": [], \"npcs\": [] }\n", 2048);
	write(p->fd, out, strlen(out));
}