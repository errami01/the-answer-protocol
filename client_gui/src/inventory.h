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

void	draw_inventory(char **items);
int		parse_inventory(const char *response, t_game *game);
void	clear_inventory(t_game *game);

#endif
