/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abuse_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 20:26:01 by aberrami          #+#    #+#             */
/*   Updated: 2026/11/28 13:07:58 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

/*
** Monitoring logic: Max 5 commands per second.
** Returns 1 if flooding is detected, 0 otherwise.
*/
int	check_flooding(t_player *p, struct pollfd *fds, int i)
{
	long	now;
	char	*name;

	now = (long)time(NULL);
	if (p->last_msg_time == now)
	{
		p->msg_count++;
	}
	else
	{
		p->last_msg_time = now;
		p->msg_count = 1;
	}
	if (p->msg_count > 5)
	{
		name = "Unknown";
		if (p->name)
			name = p->name;
		write(fds[i].fd, "ERR 903 TOO MANY REQUESTS\n", 26);
		log_event("WARN", name, "ERR 903 TOO MANY REQUESTS", p->ip);
		return (1);
	}
	return (0);
}
