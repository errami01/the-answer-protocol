/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_evt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:36:43 by msturma           #+#    #+#             */
/*   Updated: 2026/11/13 14:36:44 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	shift_items_left(t_game *game, int index)
{
	int	i;

	i = index;
	while (i < game->current->item_count - 1)
	{
		memcpy(game->current->items[i], game->current->items[i + 1],
			strlen(game->current->items[i + 1]) + 1);
		i++;
	}
	memset(game->current->items[game->current->item_count - 1], 0, 128);
}

void	add_item(t_game *game, char *item)
{
	size_t	len;

	len = strlen(item);
	if (len == 0 || len >= 127)
		return ;
	strcpy(game->current->items[game->current->item_count], item);
	game->current->item_count++;
}

void	remove_item(t_game *game, char *item)
{
	int	i;

	i = 0;
	while (i < game->current->item_count)
	{
		if (strcmp(game->current->items[i], item) == 0)
		{
			shift_items_left(game, i);
			game->current->item_count--;
			return ;
		}
		i++;
	}
}
