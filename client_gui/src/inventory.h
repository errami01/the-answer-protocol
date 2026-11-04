/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:20:16 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:20:16 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVENTORY_H
# define INVENTORY_H

# include "game.h"

void		drop_button(Rectangle button);
Rectangle	get_drop_button(Rectangle panel, int i);
Rectangle	get_inventory_panel(void);
void		draw_inventory(char **items);
int			parse_inventory(const char *response, t_game *game);
void		clear_inventory(t_game *game);
void		handle_inventory_drop(t_game *game);
void		wait_drop(t_game *game, char *buf);

#endif
