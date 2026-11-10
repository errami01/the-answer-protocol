/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 20:11:47 by aberrami          #+#    #+#             */
/*   Updated: 2026/11/09 01:27:31 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

static int	handle_other_cmd(t_player *p, char *buf, t_world *world)
{
	int	result;

	result = 1;
	if (p && strncasecmp(buf, "LOOK", 4) == 0)
		cmd_look(p, world);
	else if (p && strncasecmp(buf, "MOVE ", 5) == 0)
		cmd_move(p, buf + 5, world);
	else if (p && strncasecmp(buf, "CHAT ", 5) == 0)
		cmd_chat(p, buf + 5, world);
	else if (p && strncasecmp(buf, "TAKE ", 5) == 0)
		cmd_take(p, buf + 5, world);
	else if (p && strncasecmp(buf, "DROP ", 5) == 0)
		cmd_drop(p, buf + 5, world);
	else if (p && strncasecmp(buf, "INVENTORY", 9) == 0)
		cmd_inventory(p);
	else if (p && strncasecmp(buf, "STATUS", 5) == 0)
		cmd_status(p);
	else if (p && strncasecmp(buf, "ATTACK ", 7) == 0)
		cmd_attack(p, buf + 7, world);
	else if (p && strncasecmp(buf, "QUEST ", 6) == 0)
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

	// p = &world->players[i];
	p = get_player_by_fd(world, fds[i].fd);
	name = "Unkown";
	if (world->players[i].name)
		name = world->players[i].name;
	log_event("INFO", name, buf, NULL);
	if (p && strncasecmp(buf, "QUIT", 4) == 0)
		return (cmd_quit(fds, i, world));
	else if (!p && strncasecmp(buf, "CONNECT ", 8) == 0)
		return (cmd_connect(fds, i, buf, world));
	else if (p && strncasecmp(buf, "WHO", 3) == 0)
	{
		cmd_who(p, world);
		return (1);
	}
	return (handle_other_cmd(p, buf, world));
}

void	process_command(struct pollfd *fds, int i, t_world *world, char *buf)
{
    t_player	*p;

    p = &world->players[i];
    if (check_flooding(&world->players[i]))
		return (handle_disconnect(world, i, fds));
	if (handle_conn_msg(fds, i, buf, world))
		return ;
	else if (p && strncasecmp(buf, "QUESTS", 6) == 0)
		cmd_quests(p);
	else if (p && strncasecmp(buf, "TALK ", 5) == 0)
		cmd_talk(p, buf + 5);
	else if (p && strncasecmp(buf, "GROUP ", 6) == 0)
		cmd_group(p, buf + 6, world);
	else if (p && strncasecmp(buf, "USE_ITEM ", 9) == 0)
		cmd_use_item(p, buf + 9);
	else
		write(fds[i].fd, "ERR 400 UNKNOWN_COMMAND\n", 24);
}