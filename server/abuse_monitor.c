/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abuse_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 20:26:01 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/31 21:43:53 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mud.h"


/*
** Monitoring logic: Max 10 commands per second.
** Returns 1 if flooding is detected, 0 otherwise.
*/
int	check_flooding(t_player *p)
{
	long	now;

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
        printf("check flooding\n");
		log_event("WARN", p->name ? p->name : "Unknown", "Potential command flooding detected", p->ip);
		return (1);
	}
	return (0);
}