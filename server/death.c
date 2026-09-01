/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 11:49:39 by aberrami          #+#    #+#             */
/*   Updated: 2026/09/01 16:34:06 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mud.h"

void	handle_death(t_player *p, t_world *w)
{
	char	msg[100];

	strcpy(msg, "EVT GLOBAL CHAT server Player has fallen in battle...\n");
	broadcast_global(w, msg, -1);
	msg[strlen(msg) - 1] = '\0';
	log_event("INFO", p->name, msg, NULL);
	p->hp = 50; // Respawn with half health
	p->current_room = w->rooms; // Send back to start room
	write(p->fd, "OK You died! Respawning at Village Square...\n", 45);
	log_event("INFO", p->name, "OK You died! Respawning at Village Square...", NULL);
}