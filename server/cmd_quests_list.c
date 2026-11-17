/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quests_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 21:33:57 by aberrami          #+#    #+#             */
/*   Updated: 2026/11/17 21:52:25 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

void	remove_quest(t_player *p, t_quest *q)
{
	t_quest	*curr;

	curr = p->quests;
	while (curr)
	{
		if (curr == q)
		{
			p->quests = curr->next;
			if (curr->status == Q_ACTIVE)
				curr->status = Q_AVAILABLE;
			write(p->fd, "OK Quest Dropped\n", 17);
			log_event("INFO", p->name, "OK Quest Dropped", NULL);
			return ;
		}
		curr = curr->next;
	}
}

int	is_holding_quest(t_player *p, t_quest *q)
{
	t_quest	*curr;

	curr = p->quests;
	while (curr)
	{
		if (curr == q)
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	remove_all_quests(t_player *p)
{
	t_quest	*curr;

	curr = p->quests;
	while (curr)
	{
		if (curr->status == Q_ACTIVE)
			curr->status = Q_AVAILABLE;
		curr = curr->next;
	}
	p->quests = NULL;
}

void	cmd_quests(t_player *p)
{
	t_quest	*curr;
	char	out[1024];
	char	*st_str;
	int		first;

	strlcpy(out, "OK [", sizeof(out));
	curr = p->quests;
	first = 1;
	while (curr)
	{
		if (!first)
			strlcat(out, ", ", sizeof(out));
		st_str = "completed";
		if (curr->status == Q_ACTIVE)
			st_str = "active";
		snprintf(out + strlen(out), sizeof(out) - strlen(out),
			"{\"id\": \"%s\", \"status\": \"%s\"}", curr->id, st_str);
		first = 0;
		curr = curr->next;
	}
	strlcat(out, "]\n", sizeof(out));
	write(p->fd, out, strlen(out));
	out[strlen(out)-1] = '\0';
	log_event("INFO", p->name, out, NULL);
}
