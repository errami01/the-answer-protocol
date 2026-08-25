/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 21:58:05 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/25 19:05:33 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MUD_H
# define MUD_H

# include <poll.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

# define MAX_CLIENTS 128
# define MAX_EXITS 6
# define MAX_ROOMS 256

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
	// char			*exit_names[MAX_EXITS];
	char			*target_ids[MAX_EXITS]; /* Temporary strings from JSON */
	struct s_room	*next;
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

t_room	*load_world(char *filename);
char	*read_world_file(char *filename);
void	debug_print_world(t_room *head);
void	resolve_all_exits(t_room *head);
/* Prototypes for commands */
t_world	*fill_world(t_room *head, t_world *world);
void	handle_command(int fd, char *msg, t_world *world);
void	cmd_look(t_player *player);
void	init_player(t_player *player, int fd, char *name, t_room *start_room);

/* Helper to find player by FD */
t_player	*get_player_by_fd(t_world *world, int fd);
/* Add these to mud.h */
void	broadcast_to_room(t_world *world, t_room *room, char *msg, int exclude_fd);
void	cmd_move(t_player *p, char *arg, t_world *world);
int		get_dir_index(const char *dir);
#endif