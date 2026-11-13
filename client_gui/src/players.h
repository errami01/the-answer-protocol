/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:36:18 by msturma           #+#    #+#             */
/*   Updated: 2026/11/13 14:36:19 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYERS_H
# define PLAYERS_H

# include "game.h"

void	players(t_game *game);
void	draw_players(t_game *game);
void	wait_who(t_game *game, char *buf);

void	add_player(t_game *game, const char *name);
void	remove_player(t_game *game, const char *name);

#endif
