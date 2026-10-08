#include "client.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

void client_init(t_client *client)
{
    client->socket = -1;
    client->connected = 0;
    client->recv_buffer[0] = '\0';
}

int client_connect(t_client *client, const char *ip, int port)
{
    struct sockaddr_in addr;

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

    int flags = fcntl(client->socket, F_GETFL, 0);
    if (flags >= 0)
        fcntl(client->socket, F_SETFL, flags | O_NONBLOCK);

    return (0);
}

int client_send(t_client *client, const char *message)
{
    ssize_t bytes;

    bytes = send(
        client->socket,
        message,
        strlen(message),
        MSG_NOSIGNAL
    );

    if (bytes < 0)
    {
        perror("send");
        return (-1);
    }

    return (0);
}

int client_receive(t_client *client, char *buf, size_t size)
{
    int bytes;

    bytes = recv(
        client->socket,
        buf,
        size - 1,
        0
    );

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
    {
        /*
        ** No data available right now.
        ** This is NOT a disconnect.
        */
        return (-2);
    }

    perror("recv");
    client->connected = 0;
    return (-1);
}

void client_disconnect(t_client *client)
{
    if (client->socket >= 0)
        close(client->socket);

    client->socket = -1;
    client->connected = 0;
}
