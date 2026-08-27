/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 14:43:15 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/27 15:06:31 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

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