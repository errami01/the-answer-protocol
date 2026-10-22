/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:19:39 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 17:37:07 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "client.h"
# include "quests.h"

# define MAX_INVENTORY 32
# define MAX_QUESTS 10

# define CHAT_INPUT_SIZE 256

typedef struct s_room
{
	char	name[128];
	char	description[128];

	char	north[128];
	char	west[128];
	char	south[128];
	char	east[128];

	char	items[10][128];
	int		item_count;

	char	npcs[10][128];
	int		npc_count;
}	t_room;

typedef enum e_game_state
{
	GAME_IDLE,
	GAME_WAIT_MOVE,
	GAME_WAIT_LOOK,
	GAME_WAIT_STATUS,
	GAME_WAIT_TAKE,
	GAME_WAIT_INVENTORY,
	GAME_WAIT_TALK,
	GAME_WAIT_QUEST,
	GAME_WAIT_QUESTS,
	GAME_WAIT_ATTACK,
}	t_game_state;

typedef enum e_chat_mode
{
	CHAT_MODE_GLOBAL,
	CHAT_MODE_ROOM
}	t_chat_mode;

typedef struct s_game
{
	t_scene			base;
	t_manager		*manager;
	t_room			*current;
	t_game_state	state;

	int				inventory_open;
	char			*inventory[MAX_INVENTORY];

	int				npc_open;
	char			selected_npc[128];
	char			npc_response[512];

	int				quests_open;
	int				quest_count;
	t_quest			quests[MAX_QUESTS];

	int				hp;
	int				max_hp;

	char			notification[256];
	double			notification_time;

	char			chat[8][32];
	int				chat_count;

	char			chat_input[CHAT_INPUT_SIZE];
	int				chat_input_len;
	int				chat_input_active;
	t_chat_mode		chat_mode;

	float			chat_scroll;
	int				chat_auto_scroll;
}	t_game;

t_scene	*game_create(t_manager *manager, const char *look_init);

void	draw_quests(t_game *game);
int		parse_quests(const char *response, t_game *game);

void	wait_npc_action(t_game *game, char *buf);
void	wait_menus(t_game *game, char *buf);
void	wait_move(t_game *game, char *buf);
void	wait_status(t_game *game, char *buf);
void	wait_take(t_game *game, char *buf);
void	game_idle(t_game *game, char *buf);

void	draw_arrows(t_game *game, int center_x, int center_y);
void	draw_game_utils(t_game *game);

#endif
