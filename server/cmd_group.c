/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_group.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 20:26:06 by aberrami          #+#    #+#             */
/*   Updated: 2026/11/16 16:02:32 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

static void	group_create(t_player *p)
{
	char	out[100];

	if (p->group_id)
	{
		write(p->fd, "ERR 402 ALREADY_IN_GROUP\n", 25);
		log_event("WARN", p->name, "ERR 402 ALREADY_IN_GROUP", NULL);
		return ;
	}
	p->group_id = strdup(p->name);
	snprintf(out, sizeof(out), "OK group=%s\n", p->group_id);
	write(p->fd, out, strlen(out));
	out[strlen(out) - 1] = '\0';
	log_event("INFO", p->name, out, NULL);
}

static void	group_invite(t_player *p, char *target_name, t_world *w)
{
	t_player	*target;
	char		evt[256];

	if (!p->group_id || strcmp(p->group_id, p->name) != 0)
	{
		write(p->fd, "ERR 405 NOT_GROUP_LEADER\n", 25);
		log_event("WARN", p->name, "ERR 405 NOT_GOUP_LEADER", NULL);
		return ;
	}
	target = find_player_by_name(w, target_name);
	if (!target)
	{
		write(p->fd, "ERR 404 NAME_NOT_FOUND\n", 23);
		log_event("WARN", p->name, "ERR 404 NAME_NOT_FOUND", NULL);
		return ;
	}
	target->invited_by = strdup(p->name);
	snprintf(evt, sizeof(evt), "EVT GROUP INVITE %s\n", p->name);
	write(target->fd, evt, strlen(evt));
	evt[strlen(evt) - 1] = '\0';
	log_event("INFO", p->name, evt, NULL);
	write(p->fd, "OK\n", 3);
}

static void	group_join(t_player *p, char *leader_name, t_world *w)
{
	char	evt[256];

	if (!p->invited_by || strcmp(p->invited_by, leader_name) != 0)
	{
		write(p->fd, "ERR 403 NO_INVITE_FROM_LEADER\n", 30);
		log_event("ERR", p->name, "ERR 403 NO_INVITE_FROM_LEADER", NULL);
		return ;
	}
	if (p->group_id && strcmp(p->group_id, leader_name) == 0)
	{
		write(p->fd, "ERR 402 ALREADY_IN_GROUP\n", 25);
		log_event("WARN", p->name, "ERR 402 ALREADY_IN_GROUP", NULL);
		return ;
	}
	p->group_id = strdup(leader_name);
	snprintf(evt, sizeof(evt), "EVT GROUP JOIN %s\n", p->name);
	broadcast_group(w, p->group_id, evt, p->fd);
	evt[strlen(evt) - 1] = '\0';
	log_event("INFO", p->name, evt, NULL);
	snprintf(evt, sizeof(evt), "OK group=%s\n", p->group_id);
	write(p->fd, evt, strlen(evt));
	evt[strlen(evt) - 1] = '\0';
	log_event("INFO", p->name, evt, NULL);
}

static void	leave_group(t_player *p, t_world *w)
{
	char	evt[256];

	if (p->group_id)
	{
		snprintf(evt, sizeof(evt), "EVT GROUP LEAVE %s\n", p->name);
		broadcast_group(w, p->group_id, evt, p->fd);
		log_event("INFO", p->name, "EVT GROUP LEAVE", NULL);
		free(p->group_id);
		p->group_id = NULL;
		write(p->fd, "OK\n", 3);
	}
}

void	cmd_group(t_player *p, char *arg, t_world *w)
{
	if (strncasecmp(arg, "CREATE", 6) == 0)
		group_create(p);
	else if (strncasecmp(arg, "INVITE ", 7) == 0)
		group_invite(p, arg + 7, w);
	else if (strncasecmp(arg, "JOIN ", 5) == 0)
		group_join(p, arg + 5, w);
	else if (strncasecmp(arg, "LEAVE", 5) == 0)
		leave_group(p, w);
	else
	{
		write(p->fd, "ERR 400 INVALID_ARGUMENT\n", 25);
		log_event("WARN", p->name, "ERR 400 INVALID_ARGUMENT", NULL);
	}
}
