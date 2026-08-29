/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 14:43:15 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/29 22:57:54 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

static t_quest	*parse_quest_details(const char *js, jsmntok_t *t, int *i)
{
	t_quest	*q;
	int		num_fields;

	q = malloc(sizeof(t_quest));
	if (!q)
		return (NULL);
	memset(q, 0, sizeof(t_quest));
	num_fields = t[*i].size;
	(*i)++;
	while (num_fields-- > 0)
	{
		if (jsoneq(js, &t[*i], "id") == 0)
			q->id = strndup(js + t[*i + 1].start, t[*i + 1].end - t[*i + 1].start);
		else if (jsoneq(js, &t[*i], "desc") == 0)
			q->description = strndup(js + t[*i + 1].start, t[*i + 1].end - t[*i + 1].start);
		else if (jsoneq(js, &t[*i], "req_item_id") == 0)
			q->req_item_id = strndup(js + t[*i + 1].start, t[*i + 1].end - t[*i + 1].start);
        else if (jsoneq(js, &t[*i], "req_npc_death") == 0)
            q->req_npc_death = strndup(js + t[*i + 1].start, t[*i + 1].end - t[*i + 1].start);
        else if (jsoneq(js, &t[*i], "reward_item") == 0)
            q->reward_item = strndup(js + t[*i + 1].start, t[*i + 1].end - t[*i + 1].start);
        else if (jsoneq(js, &t[*i], "reward_hp") == 0)
            q->reward_hp = atoi(js + t[*i + 1].start);
		if (num_fields)
            (*i) += 2;
        else (*i)++;
	}
	return (q);
}
/*
** Extracts NPC data from JSON tokens.
*/
static t_npc	*parse_single_npc(const char *js, jsmntok_t *t, int *i)
{
	t_npc	*npc;
	int		obj_size;

	npc = malloc(sizeof(t_npc));
	if (!npc)
		return (NULL);
	memset(npc, 0, sizeof(t_npc));
	obj_size = t[*i].size;
	(*i)++;
	while (obj_size-- > 0)
	{
		if (jsoneq(js, &t[*i], "id") == 0)
			npc->id = strndup(js + t[*i + 1].start, t[*i + 1].end - t[*i + 1].start);
		else if (jsoneq(js, &t[*i], "name") == 0)
			npc->name = strndup(js + t[*i + 1].start, t[*i + 1].end - t[*i + 1].start);
		else if (jsoneq(js, &t[*i], "hp") == 0)
			npc->hp = atoi(js + t[*i + 1].start);
		else if (jsoneq(js, &t[*i], "hostile") == 0)
			npc->is_hostile = (strncmp(js + t[*i + 1].start, "true", 4) == 0);
		else if (jsoneq(js, &t[*i], "dialogue") == 0)
			npc->dialogue = strndup(js + t[*i + 1].start, t[*i + 1].end - t[*i + 1].start);
        else if(jsoneq(js, &t[*i], "quest") == 0)
        {
            (*i)++; // Move to the array token
            npc->quest = parse_quest_details(js, t, i);
            continue;
        }
		if(obj_size)
            (*i) += 2;
        else
            (*i)++;
	}
	return (npc);
}

/*
** Loops through the "npcs" array in a room.
*/
void	parse_npc_array(const char *js, jsmntok_t *t, int *i, t_room *room)
{
	int		array_size;
	t_npc	*new_npc;

	if (t[*i].type != JSMN_ARRAY)
		return ;
	array_size = t[*i].size;
	(*i)++;
	while (array_size-- > 0)
	{
		new_npc = parse_single_npc(js, t, i);
		if (new_npc)
		{
			new_npc->next = room->npcs;
			room->npcs = new_npc;
		}
	}
}