/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chat.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:18:10 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:18:11 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAT_H
# define CHAT_H

# define WIDTH 300
# define HEIGHT 180
# define MARGIN 20
# define PADDING 10
# define FONT_SIZE 14
# define LINE_HEIGHT 20

# include "game.h"

void	add_chat_message(t_game *game, const char *message);
void	draw_chat(t_game *game);

#endif
