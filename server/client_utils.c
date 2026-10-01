
#include "mud.h"

/*
** Accepts new connection and finds the first empty slot in the poll array.
*/
char	*accept_new_client(int server_fd, struct pollfd *fds)
{
	int		new_fd;
	int		i;
	char	*ip;
	struct	sockaddr_in	addr;
	socklen_t			len;

	len = sizeof(addr);
	new_fd = accept(server_fd, (struct sockaddr *)&addr, &len);
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
void	handle_client_msg(struct pollfd *fds, int i, t_world *world)
{
	char		buf[BUFFER_SIZE];
	int			bytes;
	t_player	*p;

	bytes = recv(fds[i].fd, buf, BUFFER_SIZE - 1, 0);
	if (bytes <= 0)
	{
		handle_disconnect(world, i, fds);
		return ;
	}
	buf[bytes-1] = '\0';
	
	p = get_player_by_fd(world, fds[i].fd);
	strlcpy(world->players[i].ip, world->incoming_ip, INET_ADDRSTRLEN);
	
	if (check_flooding(&world->players[i]))
	{
		handle_disconnect(world, i, fds);
		return;
	}
	log_event("INFO", world->players[i].name? world->players[i].name : "Unkown", buf, NULL);
	if (p && strncmp(buf, "QUIT", 4) == 0)
	{
		write(fds[i].fd, "OK bye\n", 7);
		handle_disconnect(world, i, fds);
	}
	else if (!p && strncmp(buf, "CONNECT ", 8) == 0)
	{
		/* Find first empty player slot in world->players and init */
		if (is_name_taken(buf + 8, world->players, fds[i].fd))
			return;
		init_player(&world->players[i], fds[i].fd, buf + 8, world->rooms);
	}
	else if (p && strncmp(buf, "LOOK", 4) == 0)
		cmd_look(p, world);
	else if (p && strncmp(buf, "MOVE ", 5) == 0)
    	cmd_move(p, buf + 5, world);
	else if (p && strncmp(buf, "CHAT ", 5) == 0)
		cmd_chat(p, buf + 5, world);
	else if (p && strncmp(buf, "TAKE ", 5) == 0)
		cmd_take(p, buf + 5, world);
	else if (p && strncmp(buf, "DROP ", 5) == 0)
		cmd_drop(p, buf + 5, world);
	else if (p && strncmp(buf, "INVENTORY", 9) == 0)
		cmd_inventory(p);
	else if (p && strncmp(buf, "STATUS", 5) == 0)
		cmd_status(p);
	else if (p && strncmp(buf, "ATTACK ", 7) == 0)
		cmd_attack(p, buf + 7, world);
	else if (p && strncmp(buf, "QUEST ", 6) == 0)
		cmd_quest(p, buf + 6, world);
	else if (p && strncmp(buf, "QUESTS", 6) == 0)
		cmd_quests(p);
	else if (p && strncmp(buf, "TALK ", 5) == 0)
		cmd_talk(p, buf + 5);
	else if (p && strncmp(buf, "GROUP ", 6) == 0)
		cmd_group(p, buf + 6, world);
	else
		write(fds[i].fd, "OK command_received\n", 20);
}