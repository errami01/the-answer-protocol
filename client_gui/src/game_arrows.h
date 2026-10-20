/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_arrows.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:18:52 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:18:53 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_ARROWS_H
# define GAME_ARROWS_H

void	draw_arrow_up(int x, int y, const char *room_name);
void	draw_arrow_down(int x, int y, const char *room_name);
void	draw_arrow_left(int x, int y, const char *room_name);
void	draw_arrow_right(int x, int y, const char *room_name);

#endif
