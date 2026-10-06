/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 20:30:05 by aberrami          #+#    #+#             */
/*   Updated: 2026/10/04 21:03:43 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_cli.h"
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
	char	tmp[BUFFER_SIZE + 1];

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
	}
	send(sock_fd, cmd, strlen(cmd), 0);
	printf("> ");
	fflush(stdout);
}
