/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 16:53:08 by msturma           #+#    #+#             */
/*   Updated: 2026/10/13 16:53:45 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	scene_manager_init(t_manager *manager, t_client *client)
{
	manager->current = NULL;
	manager->client = client;
}

void	scene_manager_set(t_manager *manager, t_scene *scene)
{
	if (manager->current)
		manager->current->destroy(manager->current);
	manager->current = scene;
}

void	scene_manager_update(t_manager *manager)
{
	if (!manager->current)
		return ;
	manager->current->update(manager->current);
}

void	scene_manager_draw(t_manager *manager)
{
	if (!manager->current)
		return ;
	manager->current->draw(manager->current);
}

void	scene_manager_destroy(t_manager *manager)
{
	if (!manager->current)
		return ;
	manager->current->destroy(manager->current);
	manager->current = NULL;
}
