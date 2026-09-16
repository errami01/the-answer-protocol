/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 11:35:18 by aberrami          #+#    #+#             */
/*   Updated: 2026/09/16 11:18:15 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

static int	parse_room_metadata(const char *js,
		jsmntok_t *t, int *i, t_room *room)
{
	int	is_updated;

	is_updated = 1;
	if (jsoneq(js, &t[*i], "id") == 0)
		room->id = strndup(js + t[*i + 1].start,
				t[*i + 1].end - t[*i + 1].start);
	else if (jsoneq(js, &t[*i], "name") == 0)
		room->name = strndup(js + t[*i + 1].start,
				t[*i + 1].end - t[*i + 1].start);
	else if (jsoneq(js, &t[*i], "desc") == 0)
		room->description = strndup(js + t[*i + 1].start,
				t[*i + 1].end - t[*i + 1].start);
	else
		is_updated = 0;
	if (is_updated)
		(*i) += 2;
	return (is_updated);
}

static void	parse_room_items(const char *js, jsmntok_t *t, int *i, t_room *room)
{
	int		array_size;
	char	*item_id;
	t_item	*instance;

	(*i)++;
	array_size = t[*i].size;
	while (array_size-- > 0)
	{
		(*i)++;
		item_id = strndup(js + t[*i].start, t[*i].end - t[*i].start);
		instance = spawn_item(js, t, 256, item_id);
		if (instance)
			add_item(&room->items, instance);
		free(item_id);
	}
}

static void	parse_room_exits(const char *js, jsmntok_t *t, int *i, t_room *room)
{
	int		obj_size;
	int		k;

	(*i)++;
	obj_size = t[*i].size;
	while (obj_size-- > 0)
	{
		(*i) += 2;
		k = get_dir_index(strndup(js
					+ t[(*i) - 1].start, t[(*i) - 1].end - t[(*i) - 1].start));
		room->target_ids[k] = strndup(
				js + t[*i].start, t[*i].end - t[*i].start);
	}
}

t_room	*create_room(const char *js, jsmntok_t *t, int *i)
{
	t_room	*room;
	int		obj_end;

	room = malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	memset(room, 0, sizeof(t_room));
	memset(room->target_ids, 0, sizeof(room->target_ids));
	obj_end = t[(*i)].size;
	(*i)++;
	while (obj_end-- > 0)
	{
		if (parse_room_metadata(js, t, i, room))
			continue ;
		else if (jsoneq(js, &t[*i], "exits") == 0)
			parse_room_exits(js, t, i, room);
		else if (jsoneq(js, &t[*i], "items") == 0)
			parse_room_items(js, t, i, room);
		else if (jsoneq(js, &t[*i], "npcs") == 0)
			parse_npc_array(js, t, i, room);
		if (obj_end > 0)
			(*i)++;
	}
	return (room);
}
