/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:21:29 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:21:32 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "npc.h"

Rectangle	get_npc_dialog(void)
{
	int	width;
	int	height;

	width = 500;
	height = 300;
	return ((Rectangle){
		(GetScreenWidth() - width) / 2,
		(GetScreenHeight() - height) / 2,
		width,
		height
	});
}

static Rectangle	get_npc_close_button(Rectangle dialog)
{
	return ((Rectangle){
		dialog.x + dialog.width - 40,
		dialog.y + 10,
		30,
		30
	});
}

static Rectangle	get_npc_action_button(Rectangle dialog, int index)
{
	return ((Rectangle){
		dialog.x + 30 + index * 130,
		dialog.y + 100,
		100,
		40
	});
}

static void	handle_npc_action(t_game *game, int index)
{
	if (index == 0)
		talk(game, game->selected_npc);
	else if (index == 1)
		quest(game, game->selected_npc);
	else if (index == 2)
	{
		attack(game, game->selected_npc);
		game->npc_open = false;
	}
}

void	handle_npc_dialog(t_game *game)
{
	Rectangle	dialog;
	Vector2		mouse;
	int			i;

	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		return ;
	dialog = get_npc_dialog();
	mouse = GetMousePosition();
	if (CheckCollisionPointRec(mouse, get_npc_close_button(dialog)))
	{
		game->npc_open = false;
		game->npc_response[0] = '\0';
		return ;
	}
	i = 0;
	while (i < 3)
	{
		if (CheckCollisionPointRec(mouse, get_npc_action_button(dialog, i)))
		{
			handle_npc_action(game, i);
			return ;
		}
		i++;
	}
}
