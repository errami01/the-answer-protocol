/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_attack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 11:37:57 by aberrami          #+#    #+#             */
/*   Updated: 2026/09/06 22:33:52 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"
/*
** Finds NPC in the current room by name.
*/
t_npc	*find_npc(t_npc *list, char *name)
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
static int	is_quest(const t_quest *list, const t_npc *npc)
{
	while (list)
	{
		if (list->req_npc_death
			&& (strcasecmp(list->req_npc_death, npc->name) == 0
				|| strcmp(list->req_npc_death, npc->id) == 0))
			return (1);
		list = list->next;
	}
	return (0);
}

static void	combat_log(t_player *p, t_npc *npc, t_world *w, int p_dmg)
{
	char	out[512];

	snprintf(out, sizeof(out),
		"OK {\"attacker_hp\": %d, \"target_hp\": %d, \"damage\": %d}\n",
		p->hp, npc->hp, p_dmg);
	write(p->fd, out, strlen(out));
	out[strlen(out)-1] = '\0';
	log_event("INFO", p->name, out, NULL);
	snprintf(out, sizeof(out), "EVT ROOM CHAT %s attacked %s!\n",
		p->name, npc->name);
	broadcast_to_room(w, p->current_room, out, p->fd);
	out[strlen(out)-1] = '\0';
	log_event("INFO", p->name, out, NULL);
}

static void	resolve_combat(t_player *p, t_npc *npc, t_world *w)
{
	int		p_dmg;
	int		n_dmg;

	if (!npc->hp)
	{
		write(p->fd, "OK The Goblin is dead.\n", 24);
		log_event("INFO", p->name, "OK The Goblin is dead.", NULL);
		return ;
	}
	p_dmg = (rand() % 10) + 5;
	n_dmg = (rand() % 8) + 2;
	if (is_quest(p->quests, npc))
		npc->hp -= p_dmg;
	else
	{
		write(p->fd, "OK You need a Quest to defeat the enemy.\n", 41);
		log_event("INFO", p->name,
			"OK You need a Quest to defeat the enemy.", NULL);
	}
	if (npc->hp > 0)
		p->hp -= n_dmg;
	else
		npc->hp = 0;
	combat_log(p, npc, w, p_dmg);
	handle_death(p, npc, w);
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
		log_event("WARN", p->name, "ERR 404 NPC_NOT_FOUND", NULL);
		return ;
	}
	if (!target->is_hostile)
	{
		write(p->fd, "ERR 405 NPC_NOT_HOSTILE\n", 24);
		log_event("WARN", p->name, "ERR 405 NPC_NOT_HOSTILE", NULL);
		return ;
	}
	resolve_combat(p, target, w);
}
