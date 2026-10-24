/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_linker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 12:18:07 by aberrami          #+#    #+#             */
/*   Updated: 2026/10/24 21:12:20 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"

/*
** Finds a room in the linked list by its ID string.
*/
t_room	*room_by_id(t_room *head, char *id)
{
	t_room	*curr;

	if (!id)
		return (NULL);
	curr = head;
	while (curr)
	{
		if (strcmp(curr->id, id) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

/*
** Helper to link a single room's exits.
*/
static void	link_single_room(t_room *all_rooms, t_room *room)
{
	int	i;

	i = 0;
	while (i < MAX_EXITS)
	{
		if (room->target_ids[i])
		{
			room->exits[i] = room_by_id(all_rooms, room->target_ids[i]);
			if (!room->exits[i])
				printf("Warning: Room %s leads to non-existent %s\n",
					room->id, room->target_ids[i]);
		}
		i++;
	}
}

/*
** Pass 2: Iterates through all rooms and converts target_ids to exits[].
*/
void	resolve_all_exits(t_room *head)
{
	t_room	*curr;

	curr = head;
	while (curr)
	{
		link_single_room(head, curr);
		curr = curr->next;
	}
}

t_world	*fill_world(t_room *head, t_world *world)
{
	t_room	*current;
	int		i;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		memset(&world->players[i], 0, sizeof(t_player));
		world->players[i].fd = -1;
		i++;
	}
	current = head;
	world->rooms = head;
	world->room_count = 0;
	while (current != 0)
	{
		current = current->next;
		world->room_count++;
	}
	return (world);
}
