/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   login.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:20:42 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:20:42 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "login.h"
#include "client.h"

void	handle_username_input(t_login *login)
{
	int			key;
	int			input_y;
	Rectangle	button;

	key = GetCharPressed();
	while (key > 0)
	{
		if (key >= 32 && key <= 126 && login->username_len < 63)
		{
			login->username[login->username_len++] = (char)key;
			login->username[login->username_len] = '\0';
		}
		key = GetCharPressed();
	}
	if (IsKeyPressed(KEY_BACKSPACE) && login->username_len > 0)
	{
		login->username_len--;
		login->username[login->username_len] = '\0';
	}
	input_y = (GetScreenHeight() - 40) / 2 - 30;
	button = (Rectangle){(GetScreenWidth() - BUTTON_WIDTH) / 2,
		input_y + 40 + 20, BUTTON_WIDTH, BUTTON_HEIGHT};
}

void	login_submit(t_login *login)
{
	if (login->username_len == 0)
		return ;
	login->error[0] = '\0';
	if (client_connect(login->manager->client, "127.0.0.1", 4242) < 0)
	{
		login->state = LOGIN_ERROR;
		snprintf(login->error, sizeof(login->error),
			"Could not connect to server.");
		return ;
	}
	login->state = LOGIN_WAIT_HELLO;
}

static void	login_destroy(t_scene *scene)
{
	t_login		*login;

	login = (t_login *)scene;
	free(login);
}

t_scene	*login_create(t_manager *manager)
{
	t_login		*login;

	login = malloc(sizeof(*login));
	if (!login)
		return (NULL);
	*login = (t_login){
		.base = {
		.update = login_update,
		.draw = login_draw,
		.destroy = login_destroy
	},
		.manager = manager,
		.username = "",
		.username_len = 0,
		.input_active = 0
	};
	return ((t_scene *)login);
}

void	draw_login_error(t_login *login)
{
	int	x;
	int	y;
	int	width;

	if (login->error[0] == '\0')
		return ;
	width = MeasureText(login->error, 18);
	x = (GetScreenWidth() - width) / 2;
	y = GetScreenHeight() / 2 + 110;
	DrawText(login->error, x, y, 18, RED);
}
