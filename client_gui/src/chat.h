/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chat.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:18:10 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 12:38:10 by msturma          ###   ########.fr       */
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

void		add_chat_message(t_game *game, const char *message);
void		draw_chat(t_game *game);

void		init_chat_input(t_game *game);
Rectangle	get_chatbox(void);
Rectangle	get_chat_input(void);
Rectangle	get_chat_tab(int index);
void		draw_chat_tabs(t_game *game);
void		draw_chat_input(t_game *game);
void		handle_chat(t_game *game);

#endif
