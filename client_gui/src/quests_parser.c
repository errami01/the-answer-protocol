/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quests_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:22:31 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:22:32 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quests.h"
#include "game.h"
#include "json_parser.h"

static int	extract_quest_object(const char **pos, char *object, size_t size)
{
	const char	*end;
	size_t		len;

	while (**pos == ' ' || **pos == '\t' || **pos == ',')
		(*pos)++;
	if (**pos != '{')
		return (-1);
	end = strchr(*pos, '}');
	if (!end)
		return (-1);
	len = end - *pos + 1;
	if (len >= size)
		return (-1);
	memcpy(object, *pos, len);
	object[len] = '\0';
	*pos = end + 1;
	return (0);
}

static int	parse_quest_object(const char *object, t_quest *quest)
{
	memset(quest, 0, sizeof(*quest));
	if (extract_str(object, "\"id\"",
			quest->id, sizeof(quest->id)) < 0)
		return (-1);
	if (extract_str(object, "\"status\"",
			quest->status, sizeof(quest->status)) < 0)
		return (-1);
	return (0);
}

static int	handle_parse_err(const char *response,
		t_game *game, const char **pos)
{
	if (!response || !game)
		return (-1);
	if (strncmp(response, "OK ", 3) != 0)
		return (-1);
	*pos = strchr(response + 3, '[');
	if (!pos)
		return (-1);
	(*pos)++;
	return (0);
}

int	parse_quests(const char *response, t_game *game)
{
	const char	*pos;
	char		object[512];
	int			count;

	if (handle_parse_err(response, game, &pos) < 0)
		return (-1);
	count = 0;
	while (*pos && *pos != ']' && count < MAX_QUESTS)
	{
		while (*pos == ' ' || *pos == '\t' || *pos == ',')
			pos++;
		if (*pos == ']')
			break ;
		if (extract_quest_object(&pos, object, sizeof(object)) < 0)
			return (-1);
		if (parse_quest_object(object, &game->quests[count]) < 0)
			return (-1);
		count++;
	}
	if (*pos != ']')
		return (-1);
	game->quest_count = count;
	return (0);
}
