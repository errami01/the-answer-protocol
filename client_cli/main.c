/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 18:21:17 by aberrami          #+#    #+#             */
/*   Updated: 2026/09/02 18:21:20 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"


/*
** Performs the RFC 42TAP Handshake
*/
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
	printf("Enter your name: ");
	if (!fgets(name, 127, stdin))
		return (-1);
	name[strcspn(name, "\n")] = 0;
	snprintf(buf, BUFFER_SIZE, "CONNECT %s\n", name);
	send(sock_fd, buf, strlen(buf), 0);
	bytes = recv(sock_fd, buf, BUFFER_SIZE - 1, 0);
	if (bytes <= 0 || strncmp(buf, "OK connected", 12) != 0)
		return (-1);
	printf("Connected successfully!\n\n> ");
	fflush(stdout);
	return (0);
}

/*
** Reads from Server and prints to screen
*/
void	read_server(int sock_fd)
{
	char	buf[BUFFER_SIZE];
	int		bytes;

	bytes = recv(sock_fd, buf, BUFFER_SIZE - 1, 0);
	if (bytes <= 0)
	{
		printf("\nConnection lost.\n");
		exit(0);
	}
	buf[bytes] = '\0';
	printf("\n%s\n> ", buf);
	fflush(stdout);
}

/*
** Reads from Keyboard and sends to Server
*/
/* 
** Simple translation logic to make the CLI feel like a real game
*/
void	read_keyboard(int sock_fd)
{
	char	buf[BUFFER_SIZE];
	char	cmd[BUFFER_SIZE];
    char    tmp[BUFFER_SIZE+1];

	if (!fgets(buf, BUFFER_SIZE - 1, stdin))
		return ;
	buf[strcspn(buf, "\n")] = 0;
	if (strcmp(buf, "n") == 0 || strcmp(buf, "north") == 0)
		strcpy(cmd, "MOVE north\n");
	else if (strcmp(buf, "s") == 0 || strcmp(buf, "south") == 0)
		strcpy(cmd, "MOVE south\n");
	else if (strcmp(buf, "l") == 0 || strcmp(buf, "look") == 0)
		strcpy(cmd, "LOOK\n");
	else if (strncmp(buf, "say ", 4) == 0)
		snprintf(cmd, BUFFER_SIZE, "CHAT ROOM %s\n", buf + 4);
	else
    {
        snprintf(tmp, sizeof(tmp), "%s\n", buf);
        strcpy(cmd, tmp);
		// snprintf(cmd, BUFFER_SIZE, "%s\n", buf); // Raw command
    }
	send(sock_fd, cmd, strlen(cmd), 0);
	printf("> ");
	fflush(stdout);
}

int	main(int ac, char **av)
{
	int				sock_fd;
	struct sockaddr_in	serv_addr;
	struct pollfd	fds[2];

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
	fds[0].fd = 0; // Stdin
	fds[0].events = POLLIN;
	fds[1].fd = sock_fd;
	fds[1].events = POLLIN;
	while (poll(fds, 2, -1) > 0)
	{
		if (fds[1].revents & POLLIN)
			read_server(sock_fd);
		if (fds[0].revents & POLLIN)
			read_keyboard(sock_fd);
	}
	return (0);
}