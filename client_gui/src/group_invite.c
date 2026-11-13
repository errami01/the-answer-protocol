/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_invite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:37:13 by msturma           #+#    #+#             */
/*   Updated: 2026/11/13 14:37:14 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "notification.h"

void	group_invite_receive(t_game *game, char *buf)
{
	char	*prefix;
	char	*sender;
	size_t	len;

	prefix = "EVT GROUP INVITE ";
	sender = buf + strlen(prefix);
	len = strcspn(sender, "\r\n");
	if (len == 0 || len >= sizeof(game->group_invite_sender))
		return ;
	memcpy(game->group_invite_sender, sender, len);
	game->group_invite_sender[len] = '\0';
	game->group_invite_open = 1;
}

void	wait_invite_accept(t_game *game, char *buf)
{
	if (game->state != GAME_WAIT_GROUP_INVITE_ACCEPT)
		return ;
	if (strncmp(buf, "OK", 2) == 0)
	{
		game->group_invite_open = 0;
		game->group_joined = 1;
		strcpy(game->group_leader, game->group_invite_sender);
		game->group_invite_sender[0] = '\0';
		game->state = GAME_IDLE;
		return ;
	}
	show_notification(game, "Couldn't accept group invite.");
	game->state = GAME_IDLE;
}
