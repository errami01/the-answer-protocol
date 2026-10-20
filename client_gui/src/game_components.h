/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_components.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:19:21 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:19:22 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_COMPONENTS_H
# define GAME_COMPONENTS_H

# define LIST_WIDTH 180
# define LIST_HEIGHT 32
# define LIST_SPACING 8
# define LIST_MARGIN 20

# include <raylib.h>
# include "game.h"

Rectangle	get_item_button(int index);
void		draw_items(t_game *game);
void		draw_npcs(t_game *game);
void		handle_item_clicks(t_game *game);
void		handle_movement_buttons(t_game *game);
int			get_npc_start_y(t_game *game);

#endif
