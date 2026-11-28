/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 11:49:39 by aberrami          #+#    #+#             */
/*   Updated: 2026/11/28 12:58:27 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

static void	respawn(t_player *p, t_world *w)
{
	char	msg[100];
	t_room	*old_rm;

	p->hp = 50;
	old_rm = p->current_room;
	snprintf(msg, 256, "EVT ROOM PRESENCE LEAVE %s\n", p->name);
	broadcast_to_room(w, old_rm, msg, p->fd);
	msg[strlen(msg) -1] = '\0';
	log_event("INFO", p->name, msg, NULL);
	p->current_room = w->rooms;
	snprintf(msg, 256, "EVT ROOM PRESENCE ENTER %s\n", p->name);
	broadcast_to_room(w, p->current_room, msg, p->fd);
	msg[strlen(msg) -1] = '\0';
	broadcast_stats(w, p->current_room, old_rm, 0);
	log_event("INFO", p->name, msg, NULL);
}

void	handle_death(t_player *p, t_npc *npc, t_world *w)
{
	char	msg[100];
	t_item	*item;

	if (npc->hp <= 0)
	{
		item = find_item(p->current_room->items, "item.goblin_power");
		item->is_visible = 1;
		free(npc->dialogue);
		npc->dialogue = strndup("....", 4);
	}
	if (p->hp <= 0)
	{
		strcpy(msg, "EVT GLOBAL CHAT server Player has fallen in battle...\n");
		broadcast_global(w, msg, -1);
		msg[strlen(msg) - 1] = '\0';
		log_event("INFO", p->name, msg, NULL);
		write(p->fd, "OK You died! Respawning at Village Square...\n", 45);
		log_event("INFO", p->name,
			"OK You died! Respawning at Village Square...", NULL);
		respawn(p, w);
	}
}
