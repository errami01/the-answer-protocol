/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 20:11:47 by aberrami          #+#    #+#             */
/*   Updated: 2026/11/27 23:30:17 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

static int	handle_other_cmd(t_player *p, char *buf, t_world *world)
{
	int	result;

	result = 1;
	if (p->name && strncasecmp(buf, "LOOK", 4) == 0)
		cmd_look(p, world);
	else if (p->name && strncasecmp(buf, "MOVE ", 5) == 0)
		cmd_move(p, buf + 5, world);
	else if (p->name && strncasecmp(buf, "CHAT ", 5) == 0)
		cmd_chat(p, buf + 5, world);
	else if (p->name && strncasecmp(buf, "TAKE ", 5) == 0)
		cmd_take(p, buf + 5, world);
	else if (p->name && strncasecmp(buf, "DROP ", 5) == 0)
		cmd_drop(p, buf + 5, world);
	else if (p->name && strncasecmp(buf, "INVENTORY", 9) == 0)
		cmd_inventory(p);
	else if (p->name && strncasecmp(buf, "STATUS", 5) == 0)
		cmd_status(p);
	else if (p->name && strncasecmp(buf, "ATTACK ", 7) == 0)
		cmd_attack(p, buf + 7, world);
	else if (p->name && strncasecmp(buf, "QUEST ", 6) == 0)
		cmd_quest(p, buf + 6, world);
	else
		result = 0;
	return (result);
}

static int	handle_conn_msg(struct pollfd *fds, int i, char *buf,
	t_world *world)
{
	t_player	*p;
	char		*name;

	p = &world->players[i];
	name = "Unkown";
	if (p->name)
		name = world->players[i].name;
	log_event("INFO", name, buf, NULL);
	if (strncasecmp(buf, "QUIT", 4) == 0)
		return (cmd_quit(fds, i, world));
	else if (!p->name && strncasecmp(buf, "CONNECT ", 8) == 0)
		return (cmd_connect(fds, i, buf, world));
	else if (p->name && strncasecmp(buf, "WHO", 3) == 0)
	{
		cmd_who(p, world);
		return (1);
	}
	return (handle_other_cmd(p, buf, world));
}

int	contains_control_chars(const char *str, t_world *world, int i,
	struct pollfd *fds)
{
	unsigned char	*s;
	char			*name;
	t_player		*p;

	s = (unsigned char *)str;
	p = &world->players[i];
	while (*s)
	{
		if (*s == '\n' || *s == '\t')
		{
			s++;
			continue ;
		}
		if (*s < 32 || *s == 127)
		{
			name = "Unknown";
			if (p->name)
				name = p->name;
			write(fds[i].fd, "ERR 400 MALICIOUS_INPUT\n", 24);
			log_event("WARN", name, "ERR 400 MALICIOUS_INPUT", p->ip);
			return (1);
		}
		s++;
	}
	return (0);
}

void	process_command(struct pollfd *fds, int i, t_world *world, char *buf)
{
	t_player	*p;

	p = &world->players[i];
	if (check_flooding(p, fds, i))
		return (handle_disconnect(world, i, fds));
	if (contains_control_chars(buf, world, i, fds))
		return ;
	if (handle_conn_msg(fds, i, buf, world))
		return ;
	else if (p->name && strncasecmp(buf, "QUESTS", 6) == 0)
		cmd_quests(p);
	else if (p->name && strncasecmp(buf, "TALK ", 5) == 0)
		cmd_talk(p, buf + 5);
	else if (p->name && strncasecmp(buf, "GROUP ", 6) == 0)
		cmd_group(p, buf + 6, world);
	else if (p->name && strncasecmp(buf, "USE_ITEM ", 9) == 0)
		cmd_use_item(p, buf + 9);
	else
		write(fds[i].fd, "ERR 400 UNKNOWN_COMMAND\n", 24);
}
