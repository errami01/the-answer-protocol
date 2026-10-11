/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 11:27:03 by aberrami          #+#    #+#             */
/*   Updated: 2026/10/09 11:38:44 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

static void	cleanup_quest(t_quest *quest)
{
	if (!quest)
		return ;
	free(quest->id);
	free(quest->description);
	free(quest->req_item_id);
	free(quest->req_npc_death);
	free(quest->reward_item);
	free(quest);
}

static void	cleanup_ncp(t_npc *npc)
{
	t_npc	*curr;
	t_npc	*prev;

	curr = npc;
	while (curr)
	{
		free(curr->id);
		free(curr->name);
		free(curr->dialogue);
		cleanup_quest(curr->quest);
		prev = curr;
		curr = curr->next;
		free(prev);
	}
}

static void	cleanup_items(t_item *item)
{
	t_item	*curr;
	t_item	*prev;

	curr = item;
	while (curr)
	{
		free(curr->id);
		free(curr->name);
		free(curr->description);
		prev = curr;
		curr = curr->next;
		free(prev);
	}
}

static void	cleanup_target_ids(char **target_ids)
{
	int	i;

	i = 0;
	while (i < MAX_EXITS)
	{
		free(target_ids[i]);
		i++;
	}
}

void	cleanup_rooms(t_world *world)
{
	t_room	*curr;
	t_room	*next;

	curr = world->rooms;
	while (curr)
	{
		next = curr->next;
		free(curr->id);
		free(curr->name);
		free(curr->description);
		cleanup_items(curr->items);
		cleanup_ncp(curr->npcs);
		cleanup_target_ids(curr->target_ids);
		free(curr);
		curr = next;
	}
}
