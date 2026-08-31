/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 21:30:19 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/30 23:06:09 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mud.h"


/*
** Logic to complete a quest if the player has the required item.
*/

static void	complete_quest(t_player *p, t_quest *q)
{
	t_item	*item;

	item = remove_item(&p->inventory, q->req_item_id);
	if (item)
	{
		q->status = Q_COMPLETED;
		p->hp = 100;
		free(item->id);
		free(item->name);
		free(item);
		write(p->fd, "OK Quest Completed! Reward: Full HP.\n", 37);
		log_event("INFO", p->name, "OK Quest Completed! Reward: Full HP.");
	}
	else
	{
		write(p->fd, "OK You still need the item for this quest.\n", 43);
		log_event("INFO", p->name, "OK You still need the item for this quest.");
		
	}
}

static void	add_quest(t_quest **list, t_quest *new_quest)
{
	if (!new_quest)
		return ;
	new_quest->next = *list;
	*list = new_quest;
}
/*
** Handles starting a new quest or checking completion.
*/
static void	handle_quest_logic(t_player *p, t_npc *npc)
{
	t_quest	*q;
	char	out[512];

	q = npc->quest; // Assume NPC has one quest for simplicity
	if (!q || q->status == Q_COMPLETED)
	{
		write(p->fd, "ERR 406 NO_QUEST_AVAILABLE\n", 27);
		log_event("WARN", p->name, "ERR 406 NO_QUEST_AVAILABLE");
		return ;
	}
	if (q->status == Q_AVAILABLE)
	{
		q->status = Q_ACTIVE;
		snprintf(out, sizeof(out), "OK {\"quest_id\": \"%s\", \"desc\": \"%s\"}\n",
			q->id, q->description);
		add_quest(&p->quests, q);
		write(p->fd, out, strlen(out));
		out[strlen(out) - 1] = '\0';
		log_event("INFO", p->name, out);
	}
	else if (q->status == Q_ACTIVE)
		complete_quest(p, q);
}

void	cmd_quest(t_player *p, char *arg, t_world *w)
{
	t_npc	*npc;

	(void)w;
	if (!arg || strlen(arg) == 0)
		return ;
	npc = find_npc(p->current_room->npcs, arg);
	if (!npc)
	{
		write(p->fd, "ERR 404 NPC_NOT_FOUND\n", 22);
		log_event("WARN", p->name, "ERR 404 NPC_NOT_FOUND");
	}
	else
		handle_quest_logic(p, npc);
}