/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:21:47 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:21:47 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPC_H
# define NPC_H

# include "game.h"
# include <raylib.h>

typedef struct s_text_wrap
{
	Rectangle	bounds;
	int			font_size;
	Color		color;
	float		x;
	float		y;
}	t_text_wrap;

typedef enum e_dialog_state
{
	NPC_WAIT_ACTION,
	NPC_WAIT_TALK,
	NPC_WAIT_QUEST,
	NPC_WAIT_ATTACK
}	t_dialog_state;

Rectangle	get_npc_dialog(void);
void		draw_npc_dialog(t_game *game);
void		handle_npc_dialog(t_game *game);
void		talk(t_game *game, const char *npc);
void		quest(t_game *game, const char *npc);
void		attack(t_game *game, const char *npc);
int			parse_quest(const char *response, t_game *game);
void		draw_text_wrapped(const char *text, Rectangle bounds,
				int font_size, Color color);

#endif
