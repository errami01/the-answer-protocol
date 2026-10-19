/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 16:54:15 by msturma           #+#    #+#             */
/*   Updated: 2026/10/13 16:57:12 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "game_utils.h"
#include "notification.h"
#include "npc.h"
#include <string.h>

void	talk(t_game *game, const char *npc)
{
	char	cmd[256];

	snprintf(cmd, sizeof(cmd), "TALK %s\n", npc);
	game->npc_response[0] = '\0';
	if (client_send(game->manager->client, cmd) < 0)
		show_notification(game, "Failed to talk.");
	game->state = GAME_WAIT_TALK;
}

void	quest(t_game *game, const char *npc)
{
	char	cmd[256];

	snprintf(cmd, sizeof(cmd), "QUEST %s\n", npc);
	game->npc_response[0] = '\0';
	if (client_send(game->manager->client, cmd) < 0)
		show_notification(game, "Failed to take quest.");
	game->state = GAME_WAIT_QUEST;
}

void	attack(t_game *game, const char *npc)
{
	char	cmd[256];

	snprintf(cmd, sizeof(cmd), "ATTACK %s\n", npc);
	if (client_send(game->manager->client, cmd) < 0)
		show_notification(game, "Failed to attack.");
	game->state = GAME_WAIT_ATTACK;
}
