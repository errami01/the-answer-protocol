#include <errno.h>
#include <raylib.h>
#include <sys/socket.h>
#include "client.h"

static bool	client_can_send(t_client *client)
{
	double	now;

	if (client->socket < 0 || client->pending_count == 0)
		return (false);
	now = get_time();
	if (now - client->last_send_time < COMMAND_INTERVAL)
		return (false);
	return (true);
}

static void	client_remove_pending(t_client *client)
{
	client->pending_count--;
	if (client->pending_count > 0)
		memmove(client->pending[0], client->pending[1],
			client->pending_count * sizeof(client->pending[0]));
}

static void	client_send_pending(t_client *client)
{
	ssize_t	sent;
	size_t	len;

	len = strlen(client->pending[0]);
	sent = send(client->socket, client->pending[0],
			len, MSG_NOSIGNAL);
	if (sent < 0)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
			return ;
		perror("send");
		client_disconnect(client);
		return ;
	}
	if ((size_t)sent != len)
	{
		fprintf(stderr, "Partial command sent\n");
		client_disconnect(client);
		return ;
	}
	client->last_send_time = get_time();
	client_remove_pending(client);
}

void	client_update(t_client *client)
{
	if (!client)
		return ;
	if (!client_can_send(client))
		return ;
	client_send_pending(client);
}
