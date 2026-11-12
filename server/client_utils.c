/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 20:29:20 by aberrami          #+#    #+#             */
/*   Updated: 2026/11/12 15:50:46 by aberrami         ###   ########.fr       */
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

void	handle_client_msg(struct pollfd *fds, int i, t_world *world)
{
	char		tmp[BUFFER_SIZE];
	char		*newline;
	t_player	*p;
	int			bytes;
	int			remaining;

	bytes = recv(fds[i].fd, tmp, BUFFER_SIZE - 1, 0);
	if (bytes <= 0)
		return (handle_disconnect(world, i, fds));
	p = &world->players[i];
	memcpy(p->recv_buf + p->buf_len, tmp, bytes);
	p->buf_len += bytes;
	p->recv_buf[p->buf_len] = '\0';
	strlcpy(world->players[i].ip, world->incoming_ip, INET_ADDRSTRLEN);
	newline = strchr(p->recv_buf, '\n');
	while (newline != NULL)
	{
		*newline = '\0';
		process_command(fds, i, world, p->recv_buf);
		remaining = p->buf_len - (newline - p->recv_buf + 1);
		memmove(p->recv_buf, newline + 1, remaining);
		p->buf_len = remaining;
		newline = strchr(p->recv_buf, '\n');
	}
}
