/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notification.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:21:17 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:21:18 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOTIFICATION_H
# define NOTIFICATION_H

# include "game.h"

# define DURATION 5.0

void	show_notification(t_game *game, const char *text);
void	draw_notification(t_game *game);

#endif
