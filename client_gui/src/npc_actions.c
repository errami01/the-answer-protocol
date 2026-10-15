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

#include "game_utils.h"
#include "npc.h"

void	talk(t_game *game, const char *npc)
{
	char	cmd[256];

	snprintf(cmd, sizeof(cmd), "TALK %s\n", npc);
	game->npc_response[0] = '\0';
	if (client_send(game->manager->client, cmd) < 0)
		return ;
	game->state = GAME_WAIT_TALK;
}

void	quest(t_game *game, const char *npc)
{
	char	cmd[256];

	snprintf(cmd, sizeof(cmd), "QUEST %s\n", npc);
	game->npc_response[0] = '\0';
	if (client_send(game->manager->client, cmd) < 0)
		return ;
	game->state = GAME_WAIT_QUEST;
}

void	attack(t_game *game, const char *npc)
{
	char	cmd[256];

	snprintf(cmd, sizeof(cmd), "ATTACK %s\n", npc);
	if (client_send(game->manager->client, cmd) < 0)
		return ;
}

int	parse_quest(const char *response, t_game *game)
{
	if (extract_json_string(response,
			"desc", game->npc_response,
			sizeof(game->npc_response)) < 0)
	{
		strncpy(game->npc_response, response + 3, sizeof(game->npc_response));
		game->npc_response[sizeof(game->npc_response) - 1] = '\0';
	}
	return (0);
}
