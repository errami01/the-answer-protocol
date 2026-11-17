/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_talk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 11:07:19 by aberrami          #+#    #+#             */
/*   Updated: 2026/11/17 21:35:51 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

static void	set_dialogue(t_npc *npc)
{
	if (npc->quest)
	{
		free(npc->dialogue);
		if (npc->quest->status == Q_ACTIVE)
			npc->dialogue = strndup("The quest has already been taken", 32);
		else if (npc->quest->status == Q_COMPLETED)
			npc->dialogue = strndup("The quest has already been completed", 36);
		else
			npc->dialogue = strndup("I have a Quest for you", 22);
	}
}

static void	handle_talk_logic(t_player *p, t_npc *npc)
{
	char	dialogue[500];
	size_t	len;

	memset(dialogue, 0, 500);
	if (npc->dialogue)
	{
		set_dialogue(npc);
		len = strlen(npc->dialogue);
		snprintf(dialogue, sizeof(dialogue), "OK %s", npc->dialogue);
		len = strlen(dialogue);
		dialogue[len] = '\n';
		dialogue[len + 1] = '\0';
		write(p->fd, dialogue, strlen(dialogue));
	}
	else
	{
		write(p->fd, "OK I have nothing to say\n", 25);
		strncpy(dialogue, "OK I have nothing to say", 25);
		len = strlen(dialogue);
	}
	dialogue[len] = '\0';
	log_event("INFO", p->name, dialogue, NULL);
}

void	cmd_talk(t_player *p, char *arg)
{
	t_npc	*npc;

	npc = find_npc(p->current_room->npcs, arg);
	if (!npc)
	{
		write(p->fd, "ERR 404 NPC_NOT_FOUND\n", 22);
		log_event("WARN", p->name, "ERR 404 NPC_NOT_FOUND", NULL);
	}
	else
		handle_talk_logic(p, npc);
}
