/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 11:35:18 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/29 22:59:06 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mud.h"


void	parse_room_items(const char *js, jsmntok_t *t, int *i, t_room *room)
{
	int		array_size;
	char	*item_id;
	t_item	*instance;

	array_size = t[*i].size;
	while (array_size-- > 0)
	{
		(*i)++; /* Move past array token */
		item_id = strndup(js + t[*i].start, t[*i].end - t[*i].start);
		/* Logic: Search the global templates for this ID and create instance */
		instance = spawn_item(js, t, 256, item_id);
		if (instance){
			add_item(&room->items, instance);
		}
		free(item_id);
	}
}