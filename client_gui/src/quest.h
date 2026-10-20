/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quest.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:22:04 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:22:05 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEST_H
# define QUEST_H

# include "game.h"

int		parse_quest(const char *response, t_game *game);
void	quest_state(t_game *game, char *buf);

#endif
