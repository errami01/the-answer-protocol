/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_commands.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:19:09 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:19:10 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_COMMANDS_H
# define GAME_COMMANDS_H

# include "game.h"

void	move(t_game *game, const char *direction);
void	take(t_game *game, const char *item);
void	inventory(t_game *game);
void	quests(t_game *game);
void	status(t_game *game);

#endif
