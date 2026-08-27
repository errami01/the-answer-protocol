/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 12:34:17 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/27 16:02:55 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <arpa/inet.h>
#include "mud.h"

#define MAX_CLIENTS 128
#define PORT 4242
#define BUFFER_SIZE 1024

/*
** Closes the socket and resets the pollfd structure to prevent polling -1.
*/
void	cleanup_client(struct pollfd *fds, int i)
{
	close(fds[i].fd);
	fds[i].fd = -1;
	fds[i].events = 0;
	fds[i].revents = 0;
	printf("Log: Player disconnected.\n");
}

/*
** Accepts new connection and finds the first empty slot in the poll array.
*/
void	accept_new_client(int server_fd, struct pollfd *fds)
{
	int	new_fd;
	int	i;

	new_fd = accept(server_fd, NULL, NULL);
	if (new_fd < 0)
		return ;
	i = 1;
	while (i < MAX_CLIENTS)
	{
		if (fds[i].fd == -1)
		{
			fds[i].fd = new_fd;
			fds[i].events = POLLIN;
			write(new_fd, "OK hello proto=1\n", 17);
			return ;
		}
		i++;
	}
	write(new_fd, "ERR 900 CONNECTION_FAILED\n", 26);
	close(new_fd);
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
		cleanup_client(fds, i);
		return ;
	}
	buf[bytes-1] = '\0';
	p = get_player_by_fd(world, fds[i].fd);
	if (p && strncmp(buf, "QUIT", 4) == 0)
	{
		write(fds[i].fd, "OK bye\n", 7);
		cleanup_client(fds, i);
	}
	else if (!p && strncmp(buf, "CONNECT ", 8) == 0)
	{
		/* Find first empty player slot in world->players and init */
		init_player(&world->players[i], fds[i].fd, buf + 8, world->rooms);
		write(fds[i].fd, "OK connected\n", 13);
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
	else
		write(fds[i].fd, "OK command_received\n", 20);
}

/*
** Initializes the server socket with SO_REUSEADDR.
*/
int	init_server_socket(void)
{
	int					s_fd;
	int					opt;
	struct sockaddr_in	addr;

	opt = 1;
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (s_fd < 0)
		return (-1);
	setsockopt(s_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	if (bind(s_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		return (-1);
	if (listen(s_fd, 10) < 0)
		return (-1);
	return (s_fd);
}

int	main(void)
{
	int				server_fd;
	struct pollfd	fds[MAX_CLIENTS];
	int				i;
	t_room			*world_map;
	t_world			world;

	server_fd = init_server_socket();
	if (server_fd < 0)
		return (1);
	i = 0;
	while (i < MAX_CLIENTS)
		fds[i++].fd = -1;
	fds[0].fd = server_fd;
	fds[0].events = POLLIN;
	world_map = load_world("world.json");
	fill_world(world_map, &world);
	if (!world_map)
	{
		fprintf(stderr, "Error: Failed to load world.json\n");
		return (1);
	}
	// debug_print_world(world_map);

	while (1)
	{
		if (poll(fds, MAX_CLIENTS, -1) < 0)
			break ;
		if (fds[0].revents & POLLIN)
			accept_new_client(server_fd, fds);
		i = 1;
		while (i < MAX_CLIENTS)
		{
			if (fds[i].fd != -1 && (fds[i].revents & POLLIN))
				handle_client_msg(fds, i, &world);
			i++;
		}
	}
	return (0);
}
