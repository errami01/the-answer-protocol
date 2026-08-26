/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 21:56:43 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/26 23:24:40 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mud.h"


void	add_item(t_item **list, t_item *item)
{
	if (!item)
		return ;
	item->next = *list;
	*list = item;
}

/*
** Removes item from list by ID or Display Name. 
** Supports multi-word comparison.
*/
t_item	*remove_item(t_item **list, char *id_or_name)
{
	t_item	*curr;
	t_item	*prev;

	curr = *list;
	prev = NULL;
	while (curr)
	{
		if (strcmp(curr->id, id_or_name) == 0 || \
			strcasecmp(curr->name, id_or_name) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*list = curr->next;
			curr->next = NULL;
			return (curr);
		}
		prev = curr;
		curr = curr->next;
	}
	return (NULL);
}

t_item	*spawn_item(const char *js, jsmntok_t *t, int count, char *id)
{
	t_item	*new_item;
	int		i;
	int		templates_size;
	int		item_size;
	i = 0;
	while (i < count)
	{
		if (jsoneq(js, &t[i], "item_templates") == 0 && \
			t[i + 1].type == JSMN_ARRAY)
		{
			i++;
			templates_size = t[i].size;
			i++;
			while (templates_size-- > 0){
				if (jsoneq(js, &t[i + 1], "id") == 0 && \
					strncmp(js + t[i + 2].start, id, t[i + 2].end - t[i + 2].start) == 0)
				{
					item_size = t[i].size;
					new_item = malloc(sizeof(t_item));
					if (!new_item)
						return (NULL);
					memset(new_item, 0, sizeof(t_item));
					new_item->id = strdup(id);
					i += 3;
					while(item_size-- > 0){
						/* Note: In a real implementation, you'd also strdup the 'name' 
						   by searching further in this JSON object */
						if(jsoneq(js, &t[i], "name") == 0)
							new_item->name = strndup(js + t[i + 1].start, t[i + 1].end - t[i + 1].start);
						else if (jsoneq(js, &t[i], "desc") == 0)
							new_item->description = strndup(\
								js + t[i + 1].start, t[i + 1].end - t[i + 1].start);
						i += 2;	
					}
					return (new_item);
				}
				i++;
			}
			
		}
		i++;
	}
	return (NULL);
}