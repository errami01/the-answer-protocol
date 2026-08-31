/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 22:11:24 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/31 14:43:33 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"


static int is_valid_name(char *str)
{
    int start = 0;
    int end = strlen(str) - 1;

    // 1. Move start index forward past leading spaces
    while (str[start] != '\0' && isspace((unsigned char)str[start])) {
        start++;
    }

    // 2. Move end index backward past trailing spaces
    while (end >= start && isspace((unsigned char)str[end])) {
        end--;
    }

    int trimmed_len = end - start + 1;
    
    if (trimmed_len >= 3)
    {
        // 3. Shift characters left to overwrite leading spaces
        int i;
        for (i = 0; i < trimmed_len; i++) {
            str[i] = str[start + i];
        }
        
        // 4. Null-terminate the newly shifted string
        str[i] = '\0';
        
        return (1);
    }
    return (0);
}

int	is_name_taken(const char *name, const t_player *players, int fd)
{
	int	i;

	i = 0;
	// return (1);
	while (i < MAX_CLIENTS)
	{
		if (players[i].name && strcmp(players[i].name, name) == 0)
		{
			write(fd, "ERR 201 NAME_IN_USE\n", 20);
			log_event("ERROR", "SYSTEM", "ERR 201 NAME_IN_USE");
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_player(t_player *player, int fd, char *name, t_room *start_room)
{
	if (is_valid_name(name))
	{
		player->fd = fd;
		player->name = strdup(name);
		player->current_room = start_room;
		player->hp = 100;
		player->inventory = NULL;
		write(fd, "OK connected\n", 13);
		log_event("INFO", player ? player->name : "UNAUTH", name);
		return (1);
	}
	write(fd, "ERR 201 INVALID_NAME\n", 21);
	log_event("ERROR", "SYSTEM", "ERR 201 INVALID_NAME");
	return (0);

}

t_player	*get_player_by_fd(t_world *world, int fd)
{
	int	i;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (world->players[i].fd == fd)
			return (&world->players[i]);
		i++;
	}
	return (NULL);
}
