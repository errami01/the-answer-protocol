/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 20:29:20 by aberrami          #+#    #+#             */
/*   Updated: 2026/11/26 23:02:27 by aberrami         ###   ########.fr       */
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

char	*accept_new_client(int server_fd, struct pollfd *fds, t_world *w)
{
	int					new_fd;
	int					i;
	char				*ip;
	struct sockaddr_in	addr;

	new_fd = accept_new_fd(server_fd, &addr);
	if (new_fd < 0)
		return (NULL);
	i = 0;
	ip = inet_ntoa(addr.sin_addr);
	while (++i < MAX_CLIENTS)
	{
		if (fds[i].fd == -1)
		{
			fds[i].fd = new_fd;
			fds[i].events = POLLIN;
			w->players[i].buf_len = 0;
			write(new_fd, "OK hello proto=1\n", 17);
			log_event("INFO", "SYSTEM", "New connection established", ip);
			return (ip);
		}
	}
	write(new_fd, "ERR 900 CONNECTION_FAILED\n", 26);
	close(new_fd);
	return (NULL);
}

static int	validate_msg_length(int bytes, t_world *world, int i,
		struct pollfd *fds)
{
	t_player	*p;

	p = &world->players[i];
	if (bytes <= 0)
	{
		handle_disconnect(world, i, fds);
		return (0);
	}
	if (bytes + p->buf_len > 1024)
	{
		write(fds[i].fd, "ERR 400 MESSAGE_TOO_LONG\n", 25);
		log_event("ERROR", "SYSTEM", "ERR 400 MESSAGE_TOO_LONG", NULL);
		return (0);
	}
	return (1);
}

void	handle_client_msg(struct pollfd *fds, int i, t_world *world)
{
	char		tmp[BUFFER_SIZE];
	char		*newline;
	t_player	*p;
	int			bytes;
	int			remaining;

	newline = NULL;
	bytes = recv(fds[i].fd, tmp, BUFFER_SIZE - 1, 0);
	if (!validate_msg_length(bytes, world, i, fds))
		return ;
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
