/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 20:30:05 by aberrami          #+#    #+#             */
/*   Updated: 2026/11/18 11:54:45 by aberrami         ###   ########.fr       */
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
** Simple translation logic to facilitate movements between rooms
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
	else if (strcmp(buf, "e") == 0 || strcmp(buf, "east") == 0)
		strcpy(cmd, "MOVE east\n");
	else if (strcmp(buf, "w") == 0 || strcmp(buf, "west") == 0)
		strcpy(cmd, "MOVE west\n");
	else
	{
		snprintf(tmp, sizeof(tmp), "%s\n", buf);
		strcpy(cmd, tmp);
	}
	send(sock_fd, cmd, strlen(cmd), 0);
	printf("> ");
	fflush(stdout);
}
