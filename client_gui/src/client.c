/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:55:46 by msturma           #+#    #+#             */
/*   Updated: 2026/10/13 14:58:13 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

void	client_init(t_client *client)
{
	client->socket = -1;
	client->connected = 0;
	client->recv_buffer[0] = '\0';
	client->last_send_time = -COMMAND_INTERVAL;
}

int	client_connect(t_client *client, const char *ip, int port)
{
	struct sockaddr_in	addr;
	int					flags;

	client->socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client->socket < 0)
		return (-1);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0)
	{
		close(client->socket);
		client->socket = -1;
		return (-1);
	}
	if (connect(client->socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		close(client->socket);
		client->socket = -1;
		return (-1);
	}
	flags = fcntl(client->socket, F_GETFL, 0);
	if (flags >= 0)
		fcntl(client->socket, F_SETFL, flags | O_NONBLOCK);
	return (0);
}

int	client_send(t_client *client, const char *message)
{
	size_t	len;

	if (!client || !message || client->socket < 0)
		return (-1);
	len = strlen(message);
	if (len == 0 || len >= MAX_COMMAND_SIZE)
		return (-1);
	if (client->pending_count >= MAX_COMMANDS)
		return (-1);
	memcpy(client->pending[client->pending_count], message, len + 1);
	client->pending_count++;
	return (0);
}

int	client_receive(t_client *client, char *buf, size_t size)
{
	int	bytes;

	bytes = recv(client->socket, buf, size - 1, 0);
	if (bytes > 0)
	{
		buf[bytes] = '\0';
		return (bytes);
	}
	if (bytes == 0)
	{
		printf("Server closed the connection\n");
		client->connected = 0;
		return (0);
	}
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return (-2);
	perror("recv");
	client->connected = 0;
	return (-1);
}

void	client_disconnect(t_client *client)
{
	if (client->socket >= 0)
		close(client->socket);
	client->socket = -1;
	client->connected = 0;
	client->pending_count = 0;
	client->last_send_time = -COMMAND_INTERVAL;
}
