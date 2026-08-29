/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quests_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 21:33:57 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/27 21:34:25 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"
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
		st_str = (curr->status == Q_ACTIVE) ? "active" : "completed";
		snprintf(out + strlen(out), sizeof(out) - strlen(out),
			"{\"id\": \"%s\", \"status\": \"%s\"}", curr->id, st_str);
		first = 0;
		curr = curr->next;
	}
	strlcat(out, "]\n", sizeof(out));
	write(p->fd, out, strlen(out));
}