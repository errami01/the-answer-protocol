/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_components_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 15:34:25 by msturma           #+#    #+#             */
/*   Updated: 2026/10/13 16:35:09 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_arrow_buttons.h"
#include "game_commands.h"
#include "game_components.h"

Rectangle	get_item_button(int index)
{
	int	width;
	int	height;
	int	spacing;
	int	margin;

	width = 180;
	height = 32;
	spacing = 8;
	margin = 20;
	return ((Rectangle){
		GetScreenWidth() - width - margin,
		50 + index * (height + spacing),
		width,
		height
	});
}

void	handle_item_clicks(t_game *game)
{
	int			i;
	Vector2		mouse;
	Rectangle	rect;

	if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		return ;
	mouse = GetMousePosition();
	i = 0;
	while (i < game->current->item_count)
	{
		rect = get_item_button(i);
		if (CheckCollisionPointRec(mouse, rect))
		{
			take(game, game->current->items[i]);
			return ;
		}
		i++;
	}
}

static void	move_directions(t_game *game, Vector2 mouse, Rectangle *buttons)
{
	if (game->current->north[0]
		!= '\0' && CheckCollisionPointRec(mouse, buttons[0]))
	{
		move(game, "north");
		return ;
	}
	if (game->current->south[0]
		!= '\0' && CheckCollisionPointRec(mouse, buttons[1]))
	{
		move(game, "south");
		return ;
	}
	if (game->current->west[0]
		!= '\0' && CheckCollisionPointRec(mouse, buttons[2]))
	{
		move(game, "west");
		return ;
	}
	if (game->current->east[0]
		!= '\0' && CheckCollisionPointRec(mouse, buttons[3]))
	{
		move(game, "east");
		return ;
	}
}

void	handle_movement_buttons(t_game *game)
{
	Vector2		mouse;
	Rectangle	directions[4];

	if (game == NULL || game->current == NULL)
		return ;
	if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		return ;
	mouse = GetMousePosition();
	directions[0] = get_north_button();
	directions[1] = get_south_button();
	directions[2] = get_west_button();
	directions[3] = get_east_button();
	move_directions(game, mouse, directions);
}

int	get_npc_start_y(t_game *game)
{
	int	items_start_y;
	int	items_height;

	items_start_y = 50;
	items_height = game->current->item_count * (LIST_HEIGHT + LIST_SPACING);
	return (items_start_y + items_height + 30);
}
