/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_arrow_buttons.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:18:40 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:18:41 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_ARROW_BUTTONS_H
# define GAME_ARROW_BUTTONS_H

# include <raylib.h>

Rectangle	get_north_button(void);
Rectangle	get_south_button(void);
Rectangle	get_west_button(void);
Rectangle	get_east_button(void);

#endif
