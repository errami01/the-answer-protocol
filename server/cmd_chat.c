/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_chat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 21:19:15 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/25 21:19:21 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mud.h"


/*
** Formats the event message and sends it to the correct scope.
*/
static void	process_chat(t_player *p, char *scope, char *msg_text, t_world *w)
{
	char	evt[1024];

	if (strncmp(scope, "GLOBAL", 6) == 0)
	{
		snprintf(evt, sizeof(evt), "EVT GLOBAL CHAT %s %s", p->name, msg_text);
		broadcast_global(w, evt, p->fd);
	}
	else if (strncmp(scope, "ROOM", 4) == 0)
	{
		snprintf(evt, sizeof(evt), "EVT ROOM CHAT %s %s", p->name, msg_text);
		broadcast_to_room(w, p->current_room, evt, p->fd);
	}
	write(p->fd, "OK\n", 3);
}

/*
** Parses the CHAT command arguments: <scope> <message>
*/
void	cmd_chat(t_player *p, char *arg, t_world *world)
{
	char	*scope;
	char	*msg_text;

	if (!arg)
		return ;
	scope = arg;
	msg_text = strchr(arg, ' ');
	if (!msg_text)
	{
		write(p->fd, "ERR 400 INVALID_CHAT_FORMAT\n", 28);
		return ;
	}
	*msg_text = '\0';
	msg_text++;
	process_chat(p, scope, msg_text, world);
}