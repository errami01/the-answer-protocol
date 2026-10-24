/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 16:44:14 by msturma           #+#    #+#             */
/*   Updated: 2026/10/13 16:46:59 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raylib.h>
#include <stdlib.h>
#include "client.h"
#include "login.h"

void	game_loop(t_manager *manager)
{
	while (!WindowShouldClose())
	{
		scene_manager_update(manager);
		BeginDrawing();
		scene_manager_draw(manager);
		EndDrawing();
	}
}

int	get_port(int argc, char **argv)
{
	char	*end;
	long	port;

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <ip> <port>\n", argv[0]);
		return (-1);
	}
	port = strtol(argv[2], &end, 10);
	if (*end != '\0' || port < 1 || port > 65535)
	{
		fprintf(stderr, "Invalid port\n");
		return (-1);
	}
	return (port);
}

int	main(int argc, char **argv)
{
	t_scene		*scene;
	t_manager	manager;
	t_client	client;
	long		port;

	port = get_port(argc, argv);
	if (port < 0)
		return (1);
	InitWindow(1200, 800, "The Answer Protocol");
	SetTargetFPS(60);
	client_init(&client);
	scene_manager_init(&manager, &client, argv[1], (int)port);
	scene = login_create(&manager);
	if (!scene)
	{
		CloseWindow();
		return (1);
	}
	scene_manager_set(&manager, scene);
	game_loop(&manager);
	scene_manager_destroy(&manager);
	client_disconnect(&client);
	CloseWindow();
	return (0);
}
