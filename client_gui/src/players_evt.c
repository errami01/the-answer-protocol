/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_evt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:36:24 by msturma           #+#    #+#             */
/*   Updated: 2026/11/13 14:36:27 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "players.h"

void	add_player(t_game *game, const char *name)
{
	size_t	len;
	int		i;

	if (!game || !name || !*name)
		return ;
	len = strcspn(name, "\r\n");
	if (len == 0 || len >= MAX_PLAYER_NAME)
		return ;
	i = 0;
	while (i < game->room_player_count)
	{
		if (strlen(game->room_players[i]) == len
			&& strncmp(game->room_players[i], name, len) == 0)
			return ;
		i++;
	}
	if (game->room_player_count >= MAX_ROOM_PLAYERS)
		return ;
	memcpy(game->room_players[game->room_player_count], name, len);
	game->room_players[game->room_player_count][len] = '\0';
	game->room_player_count++;
}

void	remove_player(t_game *game, const char *name)
{
	size_t	len;
	int		i;

	if (!game || !name || !*name)
		return ;
	len = strcspn(name, "\r\n");
	if (len == 0)
		return ;
	i = 0;
	while (i < game->room_player_count)
	{
		if (strlen(game->room_players[i]) == len
			&& strncmp(game->room_players[i], name, len) == 0)
		{
			memmove(game->room_players[i], game->room_players[i + 1],
				(game->room_player_count - i - 1)
				* sizeof(game->room_players[0]));
			game->room_player_count--;
			game->room_players[game->room_player_count][0] = '\0';
			return ;
		}
		i++;
	}
}
