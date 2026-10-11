/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 12:34:17 by aberrami          #+#    #+#             */
/*   Updated: 2026/10/11 21:24:11 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include "mud.h"

static int	g_running = 1;

void	handle_sigint(int sig)
{
	(void)sig;
	g_running = 0;
}

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

void	cleanup_server(t_world *world)
{
	int	i;

	i = 0;
	printf("\nServer shutting down. Cleaning memory...\n");
	cleanup_rooms(world);
	while (i < MAX_CLIENTS)
	{
		if (world->players[i].fd != -1)
		{
			close(world->players[i].fd);
			free(world->players[i].name);
		}
		i++;
	}
	printf("Memory cleared. Goodbye!\n");
}

void	monitor_connection(struct pollfd *fds, int i, t_world *world,
		int server_fd)
{
	while (g_running)
	{
		if (poll(fds, MAX_CLIENTS, 1000) < 0)
			break ;
		if (fds[0].revents & POLLIN)
			strlcpy(world->incoming_ip, accept_new_client(server_fd, fds),
				INET_ADDRSTRLEN);
		i = 1;
		while (i < MAX_CLIENTS)
		{
			if (fds[i].fd != -1 && (fds[i].revents & POLLIN))
				handle_client_msg(fds, i, world);
			i++;
		}
	}
	cleanup_server(world);
}

int	main(void)
{
	int				server_fd;
	struct pollfd	fds[MAX_CLIENTS];
	int				i;
	t_room			*world_map;
	t_world			world;

	signal(SIGINT, handle_sigint);
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
	monitor_connection(fds, i, &world, server_fd);
	return (0);
}
