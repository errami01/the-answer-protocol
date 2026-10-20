/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hp.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:20:06 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:20:07 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HP_H
# define HP_H

# define BAR_WIDTH 220
# define BAR_HEIGHT 24
# define MARGIN 20

# include "game.h"

int		parse_status(char *response, t_game *game);
void	draw_hp_bar(t_game *game);

#endif
