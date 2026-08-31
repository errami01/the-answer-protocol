/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_look.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 22:13:46 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/30 22:22:17 by aberrami         ###   ########.fr       */
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
	while (i < MAX_EXITS)
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
/*
** Formats the items array in the room.
*/
static void	format_items(t_room *r, char *buf, size_t size)
{
	t_item	*curr;
	int		first;

	strlcat(buf, "], \"items\": [", size);
	curr = r->items;
	first = 1;
	while (curr)
	{
		if (curr->is_visible)
		{
			if (!first)
				strlcat(buf, ", ", size);
			strlcat(buf, "\"", size);
			strlcat(buf, curr->id, size);
			strlcat(buf, "\"", size);
			first = 0;
		}
		curr = curr->next;
	}
}

/*
** Scans the world for players in the same room and adds them to JSON.
*/
static void	format_players(t_player *p, t_world *w, char *buf, size_t size)
{
	int	i;
	int	first;

	strlcat(buf, ", \"players\": [", size);
	i = 0;
	first = 1;
	while (i < MAX_CLIENTS)
	{
		if (w->players[i].fd != -1 && \
			w->players[i].current_room == p->current_room)
		{
			if (!first)
				strlcat(buf, ", ", size);
			strlcat(buf, "\"", size);
			strlcat(buf, w->players[i].name, size);
			strlcat(buf, "\"", size);
			first = 0;
		}
		i++;
	}
}
static void	format_npcs(t_room *r, char *buf, size_t size)
{
	t_npc	*curr;
	int		first;

	strlcat(buf, "], \"npcs\": [", size);
	curr = r->npcs;
	first = 1;
	while (curr)
	{
		if (!first)
			strlcat(buf, ", ", size);
		strlcat(buf, "\"", size);
		strlcat(buf, curr->id, size);
		strlcat(buf, "\"", size);
		first = 0;
		curr = curr->next;
	}
}
/*
** Builds the full JSON response for LOOK (RFC 5.1.2).
*/
void	cmd_look(t_player *p, t_world *w)
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
	format_players(p, w, out, 2048);
	format_items(r, out, 2048);
	format_npcs(r, out, 2048);
	strlcat(out, "]}\n", 2048);
	write(p->fd, out, strlen(out));
	log_event("INFO", p->name, out);
	
}