/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 11:35:18 by aberrami          #+#    #+#             */
/*   Updated: 2026/10/03 18:43:31 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

void	cmd_status(t_player *p)
{
	char	out[256];
	char	*stat_str;

	if (p->hp > 50)
		stat_str = "healthy";
	else if (p->hp > 0)
		stat_str = "wounded";
	else
		stat_str = "dead";
	snprintf(out, sizeof(out),
		"OK {\"hp\": %d, \"max_hp\": 100, \"status\": \"%s\"}\n",
		p->hp, stat_str);
	write(p->fd, out, strlen(out));
	out[strlen(out)-1] = '\0';
	log_event("INFO", p->name, out, NULL);
}
