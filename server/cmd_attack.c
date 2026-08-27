/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_attack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 11:37:57 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/27 18:09:41 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mud.h"


/*
** Finds NPC in the current room by name.
*/
static t_npc	*find_npc(t_npc *list, char *name)
{
	while (list)
	{
		if (strcasecmp(list->name, name) == 0 || strcmp(list->id, name) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

/*
** Logic for NPC counter-attack and broadcasting results.
*/
static void	resolve_combat(t_player *p, t_npc *npc, t_world *w)
{
	int		p_dmg;
	int		n_dmg;
	char	out[512];

	p_dmg = (rand() % 10) + 5; // Player deals 5-15 dmg
	n_dmg = (rand() % 8) + 2;  // NPC deals 2-10 dmg
	npc->hp -= p_dmg;
	if (npc->hp > 0)
		p->hp -= n_dmg;
    else npc->hp = 0;
	snprintf(out, sizeof(out), 
		"OK {\"attacker_hp\": %d, \"target_hp\": %d, \"damage\": %d}\n",
		p->hp, npc->hp, p_dmg);
	write(p->fd, out, strlen(out));
	snprintf(out, sizeof(out), "EVT ROOM CHAT %s attacked %s!\n", 
		p->name, npc->name);
	broadcast_to_room(w, p->current_room, out, p->fd);
	if (p->hp <= 0)
		handle_death(p, w);
}

void	cmd_attack(t_player *p, char *arg, t_world *w)
{
	t_npc	*target;

	if (!arg || strlen(arg) == 0)
		return ;
	target = find_npc(p->current_room->npcs, arg);
	if (!target)
	{
		write(p->fd, "ERR 404 NPC_NOT_FOUND\n", 22);
		return ;
	}
	if (!target->is_hostile)
	{
		write(p->fd, "ERR 405 NPC_NOT_HOSTILE\n", 24);
		return ;
	}
	resolve_combat(p, target, w);
}