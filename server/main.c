/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 12:34:17 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/15 18:34:16 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>

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
void	handle_client_msg(struct pollfd *fds, int i)
{
	char	buf[BUFFER_SIZE];
	int		bytes;

	bytes = recv(fds[i].fd, buf, BUFFER_SIZE - 1, 0);
	if (bytes <= 0)
	{
		cleanup_client(fds, i);
		return ;
	}
	buf[bytes] = '\0';
	if (strncmp(buf, "QUIT", 4) == 0)
	{
		write(fds[i].fd, "OK bye\n", 7);
		cleanup_client(fds, i);
	}
	else if (strncmp(buf, "CONNECT ", 8) == 0)
		write(fds[i].fd, "OK connected\n", 13);
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

	server_fd = init_server_socket();
	if (server_fd < 0)
		return (1);
	i = 0;
	while (i < MAX_CLIENTS)
		fds[i++].fd = -1;
	fds[0].fd = server_fd;
	fds[0].events = POLLIN;
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
				handle_client_msg(fds, i);
			i++;
		}
	}
	return (0);
}
