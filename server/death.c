/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 11:49:39 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/27 11:50:09 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mud.h"

void	handle_death(t_player *p, t_world *w)
{
	char	*msg;

	msg = "EVT GLOBAL CHAT server Player has fallen in battle...\n";
	broadcast_global(w, msg, -1);
	p->hp = 50; // Respawn with half health
	p->current_room = w->rooms; // Send back to start room
	write(p->fd, "OK You died! Respawning at Village Square...\n", 45);
}