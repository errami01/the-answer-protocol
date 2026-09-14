/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 15:14:42 by aberrami          #+#    #+#             */
/*   Updated: 2026/09/14 18:33:41 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mud.h"

/*
** Compares a JSON token to a string.
*/
int	jsoneq(const char *json, jsmntok_t *tok, const char *s)
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
void	parse_exits(const char *js, jsmntok_t *t, int *i, t_room *room)
{
	int		obj_size;
	int		k;

	(*i)++;
	obj_size = t[*i].size;
	while(obj_size-- >0){
		(*i) += 2;
		k = get_dir_index(strndup(js + t[(*i)-1].start, t[(*i)-1].end - t[(*i)-1].start));
		room->target_ids[k] = strndup(js + t[*i].start, t[*i].end - t[*i].start);
	}
}

int	add_room_metadata(const char *js, jsmntok_t *t, int *i, t_room *room)
{
	int	is_updated;

	is_updated = 0;
	if (jsoneq(js, &t[*i], "id") == 0)
	{
		room->id = strndup(js + t[*i + 1].start, t[*i + 1].end - t[*i + 1].start);
		is_updated = 1;
	}
	else if (jsoneq(js, &t[*i], "name") == 0)
	{
		room->name = strndup(js + t[*i + 1].start, t[*i + 1].end - t[*i + 1].start);
		is_updated = 1;
	}
	else if (jsoneq(js, &t[*i], "desc") == 0)
	{
		room->description = strndup(js + t[*i + 1].start, t[*i + 1].end - t[*i + 1].start);
		is_updated = 1;
	}
	if (is_updated)
		(*i) += 2;
	return is_updated;
}

// void	add_room_prop(const char *js, jsmntok_t *t, int *i, t_room *room)
// {
	
// }
t_room	*create_room(const char *js, jsmntok_t *t, int *i)
{
	t_room	*room;
	int		obj_end;

	room = malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	memset(room, 0, sizeof(t_room));
	memset(room->target_ids, 0, sizeof(room->target_ids));
	obj_end = t[(*i)].size;
	(*i)++;
	while (obj_end-- > 0)
	{
		if (add_room_metadata(js, t, i, room))
			continue;
		else if (jsoneq(js, &t[*i], "exits") == 0)
			parse_exits(js, t, i, room);
		else if (jsoneq(js, &t[*i], "items") == 0)
		{
			(*i)++;
			parse_room_items(js, t, i, room);
		}
		else if (jsoneq(js, &t[*i], "npcs") == 0)
			parse_npc_array(js, t, i, room);
		if (obj_end > 0)
				(*i)++;
	}
	return (room);
}

/*
** Main entry for world loading. (Pass 1 only for brevity)
*/
void	creat_all_rooms(t_room **current, char *js, jsmntok_t *t, int *i)
{
	(*current)->next = create_room(js, t, i);
	*current = (*current)->next;
	(*current)->next = NULL;
	(*i)++;
}

t_room	*load_rooms(char *js, jsmntok_t *t, int r)
{
	int		i;
	int		rooms_size;
	t_room	*head;
	t_room	*current;

	i = 1;
	while (i < r)
	{
		if (jsoneq(js, &t[i], "rooms") == 0 && t[i + 1].type == JSMN_ARRAY)
		{
			rooms_size = t[i + 1].size;
			i += 2;
			head = create_room(js, t, &i);
			i++;
			if (!head)
				return (NULL);
			current = head;
			while (--rooms_size > 0)
				creat_all_rooms(&current, js, t, &i);
			resolve_all_exits(head);
			return (head);
		}
		i++;
	}
	return (NULL);
}

t_room	*load_world(char *filename)
{
	char			*js;
	jsmn_parser		p;
	jsmntok_t		t[256];
	int				r;

	js = read_world_file(filename);
	if (!js)
		return (NULL);
	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), t, 256);
	if (r < 0)
		return (NULL);
	return (load_rooms(js, t, r));
}

// int	get_dir_index(const char *dir)
// {
// 	if (strcmp(dir, "north") == 0) return (0);
// 	if (strcmp(dir, "south") == 0) return (1);
// 	if (strcmp(dir, "east") == 0)  return (2);
// 	if (strcmp(dir, "west") == 0)  return (3);
// 	if (strcmp(dir, "up") == 0)    return (4);
// 	if (strcmp(dir, "down") == 0)  return (5);
// 	return (-1);
// }

// void	debug_print_world(t_room *head)
// {
// 	t_room	*curr;
// 	int		i;

// 	curr = head;
// 	printf("\n--- WORLD MAP DEBUG ---\n");
// 	while (curr)
// 	{
// 		printf("Room: [%s] (%s)\n", curr->id, curr->name);
// 		i = 0;
// 		while (i < MAX_EXITS)
// 		{
// 			if (curr->exits[i])
// 				printf("  -> Exit %d leads to: %s\n", i, curr->exits[i]->id);
// 			i++;
// 		}
// 		curr = curr->next;
// 	}
// 	printf("-----------------------\n\n");
// }