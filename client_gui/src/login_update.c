#include "client.h"
#include "login.h"
#include "game.h"

static void	login_idle(t_login *login)
{
	if (IsKeyPressed(KEY_ENTER))
		login_submit(login);
}

static void	login_wait_hello(t_login *login)
{
	char	cmd[128];
	char	buf[BUFFER_SIZE];
	int		bytes;

	bytes = client_receive(login->manager->client, buf, sizeof(buf));
	if (bytes > 0)
	{
		if (strncmp(buf, "OK hello", 8))
		{
			login->state = LOGIN_ERROR;
			strcpy(login->error, "Invalid server handshake.");
			return ;
		}
		snprintf(cmd, sizeof(cmd), "CONNECT %s\n", login->username);
		client_send(login->manager->client, cmd);
		login->state = LOGIN_WAIT_CONNECTED;
	}
}

static void	login_wait_connected(t_login *login)
{
	char	buf[BUFFER_SIZE];
	int		bytes;

	bytes = client_receive(login->manager->client, buf, sizeof(buf));
	if (bytes > 0)
	{
		if (strncmp(buf, "OK connected", 12))
		{
			login->state = LOGIN_ERROR;
			strcpy(login->error, "Server rejected connection.");
			return ;
		}
		login->manager->client->connected = 1;
		if (client_send(login->manager->client, "LOOK\n") < 0)
		{
			login->state = LOGIN_ERROR;
			strcpy(login->error, "Failed to send LOOK.");
			return ;
		}
		login->state = LOGIN_WAIT_LOOK;
	}
}

static void	login_wait_look(t_login *login)
{
	char		buf[BUFFER_SIZE];
	int			bytes;
	t_scene		*game;

	bytes = client_receive(login->manager->client, buf, sizeof(buf));
	if (bytes > 0)
	{
		if (strncmp(buf, "OK ", 3))
		{
			login->state = LOGIN_ERROR;
			strcpy(login->error, "LOOK failed.");
			return ;
		}
		game = game_create(login->manager, buf + 3);
		if (game == NULL)
		{
			login->state = LOGIN_ERROR;
			strcpy(login->error, "Failed to create game scene.");
			return ;
		}
		scene_manager_set(login->manager, game);
	}
}

void	login_update(t_scene *scene)
{
	t_login		*login;

	login = (t_login *)scene;
	handle_username_input(login);
	if (login->state == LOGIN_IDLE)
		login_idle(login);
	if (login->state == LOGIN_WAIT_HELLO)
		login_wait_hello(login);
	if (login->state == LOGIN_WAIT_CONNECTED)
		login_wait_connected(login);
	if (login->state == LOGIN_WAIT_LOOK)
		login_wait_look(login);
}
