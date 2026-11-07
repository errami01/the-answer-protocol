/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_use_item.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 15:37:02 by aberrami          #+#    #+#             */
/*   Updated: 2026/11/07 21:50:50 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

void	cmd_use_item(t_player *p, char *arg)
{
	t_item	*item;

	if (!arg || strlen(arg) == 0)
		return ;
	item = find_item(p->inventory, arg);
	if (!item)
	{
		write(p->fd, "OK Item not found\n", 18);
		log_event("INFO", p->name, "OK Item not found", NULL);
	}
	else if (strcmp("item.shield", item->id) == 0)
	{
		p->is_defending = 1;
		write(p->fd, "OK Defence activated\n", 21);
		log_event("INFO", p->name, "OK Defence activated", NULL);
	}
}
