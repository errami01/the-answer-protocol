/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 20:29:20 by aberrami          #+#    #+#             */
/*   Updated: 2026/10/04 14:03:40 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

/*
** Accepts new connection and finds the first empty slot in the poll array.
*/
static int	accept_new_fd(int server_fd, struct sockaddr_in *addr)
{
	socklen_t	len;

	memset(addr, 0, sizeof(*addr));
	len = sizeof(*addr);
	return (accept(server_fd, (struct sockaddr *)addr, &len));
}

char	*accept_new_client(int server_fd, struct pollfd *fds)
{
	int					new_fd;
	int					i;
	char				*ip;
	struct sockaddr_in	addr;

	new_fd = accept_new_fd(server_fd, &addr);
	if (new_fd < 0)
		return (NULL);
	i = 1;
	ip = inet_ntoa(addr.sin_addr);
	while (i < MAX_CLIENTS)
	{
		if (fds[i].fd == -1)
		{
			fds[i].fd = new_fd;
			fds[i].events = POLLIN;
			write(new_fd, "OK hello proto=1\n", 17);
			log_event("INFO", "SYSTEM", "New connection established", ip);
			return (ip);
		}
		i++;
	}
	write(new_fd, "ERR 900 CONNECTION_FAILED\n", 26);
	close(new_fd);
	return (NULL);
}

/*
** Reads client message. For now, we only handle CONNECT and QUIT.
*/
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

	p = get_player_by_fd(world, fds[i].fd);
	name = "Unkown";
	if (world->players[i].name)
		name = world->players[i].name;
	log_event("INFO", name, buf, NULL);
	if (p && strncasecmp(buf, "QUIT", 4) == 0)
	{
		write(fds[i].fd, "OK bye\n", 7);
		handle_disconnect(world, i, fds);
		return (1);
	}
	else if (!p && strncasecmp(buf, "CONNECT ", 8) == 0)
	{
		if (is_name_taken(buf + 8, world->players, fds[i].fd))
			return (1);
		init_player(&world->players[i], fds[i].fd, buf + 8, world->rooms);
		return (1);
	}
	return (handle_other_cmd(p, buf, world));
}

void	handle_client_msg(struct pollfd *fds, int i, t_world *world)
{
	char		buf[BUFFER_SIZE];
	t_player	*p;
	int			bytes;

	bytes = recv(fds[i].fd, buf, BUFFER_SIZE - 1, 0);
	if (bytes <= 0)
		return (handle_disconnect(world, i, fds));
	buf[bytes - 1] = '\0';
	p = get_player_by_fd(world, fds[i].fd);
	strlcpy(world->players[i].ip, world->incoming_ip, INET_ADDRSTRLEN);
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
	else
		write(fds[i].fd, "ERR 400 UNKNOWN_COMMAND\n", 24);
}
