/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 15:14:42 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/17 21:30:27 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mud.h"
#define JSMN_STATIC
#include "./libs/jsmn.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
** Compares a JSON token to a string.
*/
static int	jsoneq(const char *json, jsmntok_t *tok, const char *s)
{
	if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start && \
		strncmp(json + tok->start, s, tok->end - tok->start) == 0)
		return (0);
	return (-1);
}

/*
** Reads the entire file into a string.
*/
char	*read_world_file(char *filename)
{
	int		fd;
	char	*buf;
	int		bytes;

	buf = malloc(10000);
	if (!buf)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(buf);
		return (NULL);
	}
	bytes = read(fd, buf, 9999);
	buf[bytes] = '\0';
	close(fd);
	return (buf);
}

/*
** Allocates a room and sets basic strings.
*/
t_room	*create_room(const char *js, jsmntok_t *t, int *i)
{
	t_room	*room;
	int		obj_end;

	room = malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	memset(room, 0, sizeof(t_room));
	obj_end = t[*i].size;
	(*i)++;
	while (obj_end-- > 0)
	{
		if (jsoneq(js, &t[*i], "id") == 0)
			room->id = strndup(js + t[*i + 1].start, t[*i + 1].end - t[*i + 1].start);
		else if (jsoneq(js, &t[*i], "name") == 0)
			room->name = strndup(js + t[*i + 1].start, t[*i + 1].end - t[*i + 1].start);
		else if (jsoneq(js, &t[*i], "desc") == 0)
			room->description = strndup(js + t[*i + 1].start, t[*i + 1].end - t[*i + 1].start);
		else if (t[*i].type == JSMN_OBJECT || t[*i].type == JSMN_ARRAY)
			(*i) += t[*i].size;
		(*i) += 2;
	}
	return (room);
}

/*
** Main entry for world loading. (Pass 1 only for brevity)
*/
t_room	*load_world(char *filename)
{
	char			*js;
	jsmn_parser		p;
	jsmntok_t		t[256];
	int				r;
	int				i;

	js = read_world_file(filename);
	if (!js)
		return (NULL);
	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), t, 256);
	if (r < 0)
		return (NULL);
	i = 1;
	while (i < r)
	{
		if (jsoneq(js, &t[i], "rooms") == 0 && t[i + 1].type == JSMN_ARRAY)
		{
			// Loop through rooms array and call create_room
			// This is where you would link your t_room list
			return (create_room(js, t, &i)); // Returns first room for now
		}
		i++;
	}
	return (NULL);
}