/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_items.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 21:59:19 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/26 22:50:23 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mud.h"


void	cmd_take(t_player *p, char *arg, t_world *w)
{
	t_item	*item;
	char	out[256];
	(void)w;
	if (!arg || strlen(arg) == 0)
		return ;
	item = remove_item(&p->current_room->items, arg);
	if (!item)
	{
		write(p->fd, "ERR 404 ITEM_NOT_FOUND\n", 23);
		return ;
	}
	add_item(&p->inventory, item);
	snprintf(out, sizeof(out), "OK taken=%s\n", item->id);
	write(p->fd, out, strlen(out));
}

void	cmd_drop(t_player *p, char *arg, t_world *w)
{
	t_item	*item;
	char	out[256];

	(void)w;
	item = remove_item(&p->inventory, arg);
	if (!item)
	{
		write(p->fd, "ERR 404 ITEM_NOT_IN_INVENTORY\n", 30);
		return ;
	}
	add_item(&p->current_room->items, item);
	snprintf(out, sizeof(out), "OK dropped=%s\n", item->id);
	write(p->fd, out, strlen(out));
}

void	cmd_inventory(t_player *p)
{
	t_item	*curr;
	char	out[1024];
	int		first;

	strlcpy(out, "OK [", sizeof(out));
	curr = p->inventory;
	first = 1;
	while (curr)
	{
		if (!first)
			strlcat(out, ", ", sizeof(out));
		strlcat(out, "\"", sizeof(out));
		strlcat(out, curr->id, sizeof(out));
		strlcat(out, "\"", sizeof(out));
		first = 0;
		curr = curr->next;
	}
	strlcat(out, "]\n", sizeof(out));
	write(p->fd, out, strlen(out));
}