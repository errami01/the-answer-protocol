/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 16:44:14 by msturma           #+#    #+#             */
/*   Updated: 2026/11/02 13:49:51 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raylib.h>
#include <stdlib.h>
#include "client.h"
#include "login.h"

void	game_loop(t_manager *manager, t_client *client)
{
	while (!WindowShouldClose())
	{
		client_update(client);
		scene_manager_update(manager);
		BeginDrawing();
		scene_manager_draw(manager);
		EndDrawing();
	}
}

int	validate_args(int argc, char **argv)
{
	struct in_addr	addr;
	char			*end;
	long			port;

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <ip> <port>\n", argv[0]);
		return (0);
	}
	if (inet_pton(AF_INET, argv[1], &addr) != 1)
	{
		fprintf(stderr, "Invalid IP: %s\n", argv[1]);
		return (0);
	}
	port = strtol(argv[2], &end, 10);
	if (argv[2][0] == '\0' || *end != '\0'
		|| port < 1 || port > 65535)
	{
		fprintf(stderr, "Invalid port: %s\n", argv[2]);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_scene		*scene;
	t_manager	manager;
	t_client	client;
	char		*end;

	if (!validate_args(argc, argv))
		return (1);
	InitWindow(1200, 800, "The Answer Protocol");
	SetTargetFPS(60);
	client_init(&client);
	scene_manager_init(&manager, &client, argv[1],
		(int)strtol(argv[2], &end, 10));
	scene = login_create(&manager);
	if (!scene)
	{
		CloseWindow();
		return (1);
	}
	scene_manager_set(&manager, scene);
	game_loop(&manager, &client);
	scene_manager_destroy(&manager);
	client_disconnect(&client);
	CloseWindow();
	return (0);
}
