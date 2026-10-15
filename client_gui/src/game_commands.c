/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 15:31:26 by msturma           #+#    #+#             */
/*   Updated: 2026/10/13 16:34:29 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_commands.h"
#include "client.h"
#include "game.h"
#include <stdio.h>

void	move(t_game *game, const char *direction)
{
	char	cmd[64];

	snprintf(cmd, sizeof(cmd), "MOVE %s\n", direction);
	if (client_send(game->manager->client, cmd) < 0)
		return ;
	game->state = GAME_WAIT_MOVE;
}

void	take(t_game *game, const char *item)
{
	char	cmd[64];

	snprintf(cmd, sizeof(cmd), "TAKE %s\n", item);
	if (client_send(game->manager->client, cmd) < 0)
		return ;
	game->state = GAME_WAIT_TAKE;
}

void	inventory(t_game *game)
{
	if (client_send(game->manager->client, "INVENTORY\n") < 0)
		return ;
	game->state = GAME_WAIT_INVENTORY;
}

void	quests(t_game *game)
{
	if (client_send(game->manager->client, "QUESTS\n") < 0)
		return ;
	game->state = GAME_WAIT_QUESTS;
}

void status(t_game *game)
{
    if (client_send(game->manager->client, "STATUS\n") < 0)
        return ;
    game->state = GAME_WAIT_STATUS; 
}
