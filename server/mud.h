/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 21:58:05 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/15 21:58:13 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MUD_H
# define MUD_H

# include <poll.h>

# define MAX_CLIENTS 128
# define MAX_EXITS 6

typedef struct s_item
{
	char			*id;
	char			*name;
	char			*description;
	struct s_item	*next;
}	t_item;

typedef struct s_room
{
	char			*id;
	char			*name;
	char			*description;
	struct s_room	*exits[MAX_EXITS];
	char			*exit_names[MAX_EXITS];
	t_item			*items;
}	t_room;

typedef struct s_player
{
	int				fd;
	char			*name;
	t_room			*current_room;
	t_item			*inventory;
	int				hp;
}	t_player;

typedef struct s_world
{
	t_room			*rooms;
	int				room_count;
	t_player		players[MAX_CLIENTS];
}	t_world;

#endif