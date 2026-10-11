/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 21:58:05 by aberrami          #+#    #+#             */
/*   Updated: 2026/10/09 21:08:21 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUD_H
# define MUD_H
# define JSMN_HEADER

# include "../libs/jsmn.h"
# include "../shared/protocol.h"

# define PORT 4242
# define BUFFER_SIZE 1024
# define MAX_CLIENTS 128
# define MAX_EXITS 6
# define MAX_ROOMS 256

typedef enum e_qstatus
{
	Q_AVAILABLE,
	Q_ACTIVE,
	Q_COMPLETED
}	t_qstatus;

typedef struct s_quest
{
	char			*id;
	char			*description;
	char			*req_item_id;
	char			*req_npc_death;
	int				reward_hp;
	char			*reward_item;
	t_qstatus		status;
	struct s_quest	*next;
}	t_quest;

typedef struct s_item
{
	char			*id;
	char			*name;
	char			*description;
	int				is_visible;
	struct s_item	*next;
}	t_item;

typedef struct s_npc
{
	char			*id;
	char			*name;
	int				hp;
	int				max_hp;
	int				is_hostile;
	char			*dialogue;
	t_quest			*quest;
	struct s_npc	*next;
}	t_npc;

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
	t_npc			*npcs;
}	t_room;

typedef struct s_player
{
	int				fd;
	char			*name;
	t_room			*current_room;
	t_item			*inventory;
	int				hp;
	char			ip[INET_ADDRSTRLEN];
	t_quest			*quests;
	long			last_msg_time;
	int				msg_count;
	char			*group_id;
	char			*invited_by;
}	t_player;

typedef struct s_world
{
	t_room			*rooms;
	int				room_count;
	t_player		players[MAX_CLIENTS];
	char			incoming_ip[INET_ADDRSTRLEN];
}	t_world;

char		*accept_new_client(int server_fd, struct pollfd *fds);
void		handle_client_msg(struct pollfd *fds, int i, t_world *world);
t_room		*load_world(char *filename);
char		*read_world_file(char *filename);
void		debug_print_world(t_room *head);
void		resolve_all_exits(t_room *head);
/* Prototypes for commands */
t_world		*fill_world(t_room *head, t_world *world);
void		handle_command(int fd, char *msg, t_world *world);
int			cmd_connect(struct pollfd *fds, int i, char *buf, t_world *world);
int			cmd_quit(struct pollfd *fds, int i, t_world *world);
void		cmd_look(t_player *player, t_world *world);
int			init_player(t_player *player, int fd, char *name,
				t_room *start_room);
int			is_name_taken(const char *name, const t_player *players, int fd);

/* Helper to find player by FD */
t_player	*get_player_by_fd(t_world *world, int fd);
/* Add these to mud.h */
void		broadcast_to_room(t_world *world, t_room *room, char *msg,
				int exclude_fd);
void		cmd_move(t_player *p, char *arg, t_world *world);
int			get_dir_index(const char *dir);
void		broadcast_global(t_world *world, char *msg, int exclude_fd);
void		cmd_chat(t_player *p, char *arg, t_world *world);
void		cmd_take(t_player *p, char *arg, t_world *w);
void		cmd_drop(t_player *p, char *arg, t_world *w);
void		cmd_inventory(t_player *p);

/* Linked List Helpers */
void		add_item(t_item **list, t_item *item);
t_item		*remove_item(t_item **list, char *id_or_name);
t_item		*find_item(t_item *list, char *name);
t_room		*create_room(const char *js, jsmntok_t *t, int *i);
void		cleanup_rooms(t_world *world);
void		cleanup_client(struct pollfd *fds, int i);
void		clean_player(t_player *p);
t_item		*spawn_item(const char *js, jsmntok_t *t, int count, char *id);
int			jsoneq(const char *json, jsmntok_t *tok, const char *s);

/* Prototypes */
void		cmd_attack(t_player *p, char *arg, t_world *w);
void		cmd_status(t_player *p);
void		handle_death(t_player *p, t_npc *npc, t_world *w);
t_npc		*remove_npc(t_npc **list, char *name); // Optional: for XP/Loot
void		parse_npc_array(const char *js, jsmntok_t *t, int *i, t_room *room);
void		cmd_quest(t_player *p, char *arg, t_world *w);
void		cmd_quests(t_player *p);
t_npc		*find_npc(t_npc *list, char *name);
void		handle_disconnect(t_world *world, int i, struct pollfd *fds);
void		log_event(const char *level, const char *player, const char *action,
				const char *ip);
int			check_flooding(t_player *p);
void		cmd_talk(t_player *p, char *arg);
void		cmd_group(t_player *p, char *arg, t_world *w);
void		broadcast_group(t_world *w, char *group_id, char *msg,
				int exclude_fd);
t_player	*find_player_by_name(t_world *w, char *name);
#endif