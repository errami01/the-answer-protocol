/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:18:59 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 17:39:21 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raylib.h>
#include <string.h>
#include "game.h"
#include "client.h"
#include "game_commands.h"
#include "game_utils.h"
#include "inventory.h"
#include "npc.h"
#include "chat.h"

static void	game_update(t_scene *scene)
{
	t_game	*game;
	char	buf[BUFFER_SIZE];
	int		bytes;

	game = (t_game *)scene;
	if (game->current == NULL)
		return ;
	handle_chat(game);
	game_idle(game, buf);
	while (1)
	{
		bytes = client_receive(game->manager->client, buf, sizeof(buf));
		if (bytes <= 0)
			return ;
		if (strncmp(buf, "EVT ", 4) == 0)
		{
			add_chat_message(game, buf + 4);
			return ;
		}
		wait_take(game, buf);
		wait_status(game, buf);
		wait_move(game, buf);
		wait_menus(game, buf);
		wait_npc_action(game, buf);
	}
}

static void	game_draw(t_scene *scene)
{
	t_game	*game;
	int		center_x;
	int		center_y;

	game = (t_game *)scene;
	ClearBackground(RAYWHITE);
	if (game->current == NULL)
	{
		DrawText("No room data", 20, 20, 20, RED);
		return ;
	}
	DrawText(TextFormat("Current Room: %s", game->current->name),
		20, 20, 20, BLACK);
	DrawText(game->current->description, 20, 60, 15, DARKGRAY);
	draw_game_utils(game);
	center_x = GetScreenWidth() / 2;
	center_y = GetScreenHeight() / 2;
	draw_arrows(game, center_x, center_y);
	draw_chat(game);
	if (game->inventory_open)
		draw_inventory(game->inventory);
	if (game->npc_open)
		draw_npc_dialog(game);
	if (game->quests_open)
		draw_quests(game);
}

static void	game_destroy(t_scene *scene)
{
	t_game	*game;

	game = (t_game *)scene;
	clear_inventory(game);
	if (game->current)
		free(game->current);
	free(game);
}

t_scene	*game_create(t_manager *manager, const char *look_init)
{
	t_game	*game;
	t_room	*room;

	game = calloc(1, sizeof(*game));
	if (!game)
		return (NULL);
	game->base.update = game_update;
	game->base.draw = game_draw;
	game->base.destroy = game_destroy;
	game->manager = manager;
	room = malloc(sizeof(*room));
	if (parse_look(look_init, room) < 0)
	{
		printf("Failed to parse look.");
		return (NULL);
	}
	game->current = room;
	game->npc_response[0] = '\0';
	status(game);
	game->chat_count = 0;
	memset(game->chat, 0, sizeof(game->chat));
	init_chat_input(game);
	init_chat_scroll(game);
	return ((t_scene *)game);
}
