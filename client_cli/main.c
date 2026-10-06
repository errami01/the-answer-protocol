/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 18:21:17 by aberrami          #+#    #+#             */
/*   Updated: 2026/10/04 21:01:29 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_cli.h"

/*
** Performs the RFC 42TAP Handshake
*/
static int	log_in(char *buf, char *name, int sock_fd)
{
	int		bytes;

	while (strncmp(buf, "OK connected", 12) != 0)
	{
		printf("Enter your name: ");
		if (!fgets(name, 127, stdin))
			return (-1);
		name[strcspn(name, "\n")] = 0;
		snprintf(buf, BUFFER_SIZE, "CONNECT %s\n", name);
		send(sock_fd, buf, strlen(buf), 0);
		bytes = recv(sock_fd, buf, BUFFER_SIZE - 1, 0);
		if (bytes <= 0)
			return (-1);
		if (strncmp(buf, "OK connected", 12) != 0)
		{
			buf[bytes] = '\0';
			printf("Server: %s", buf);
		}
	}
	printf("Connected successfully!\n\n> ");
	fflush(stdout);
	return (0);
}

static int	handle_handshake(int sock_fd)
{
	char	buf[BUFFER_SIZE];
	char	name[128];
	int		bytes;

	bytes = recv(sock_fd, buf, BUFFER_SIZE - 1, 0);
	if (bytes <= 0 || strncmp(buf, "OK hello", 8) != 0)
		return (-1);
	buf[bytes] = '\0';
	printf("Server: %s", buf);
	return (log_in(buf, name, sock_fd));
}

void	read_socket(struct pollfd *fds, int sock_fd)
{
	while (poll(fds, 2, -1) > 0)
	{
		if (fds[1].revents & POLLIN)
			read_server(sock_fd);
		if (fds[0].revents & POLLIN)
			read_keyboard(sock_fd);
	}
}

int	main(int ac, char **av)
{
	int					sock_fd;
	struct pollfd		fds[2];
	struct sockaddr_in	serv_addr;

	if (ac < 3)
		return (printf("Usage: ./client <ip> <port>\n"), 1);
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(av[2]));
	inet_pton(AF_INET, av[1], &serv_addr.sin_addr);
	if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		return (perror("Connect failed"), 1);
	if (handle_handshake(sock_fd) < 0)
		return (printf("Handshake failed\n"), 1);
	fds[0].fd = 0;
	fds[0].events = POLLIN;
	fds[1].fd = sock_fd;
	fds[1].events = POLLIN;
	read_socket(fds, sock_fd);
	return (0);
}

// while (poll(fds, 2, -1) > 0)
// 	{
// 		if (fds[1].revents & POLLIN)
// 			read_server(sock_fd);
// 		if (fds[0].revents & POLLIN)
// 			read_keyboard(sock_fd);
// 	}