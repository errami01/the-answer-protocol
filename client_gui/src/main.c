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

int	main(void)
{
	t_scene		*scene;
	t_manager	manager;
	t_client	client;

	InitWindow(1200, 800, "The Answer Protocol");
	SetTargetFPS(60);
	client_init(&client);
	scene_manager_init(&manager, &client);
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
