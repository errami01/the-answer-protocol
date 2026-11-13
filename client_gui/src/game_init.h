/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:38:05 by msturma           #+#    #+#             */
/*   Updated: 2026/11/13 14:38:06 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_INIT_H
# define GAME_INIT_H

# include "game.h"

int		init_room(t_game *game, const char *look_init);
void	init_chat(t_game *game);

#endif
