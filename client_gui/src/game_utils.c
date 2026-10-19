#include "game_utils.h"
#include "json_parser.h"

static int	parse_items(const char *response, t_room *room)
{
	room->item_count = extract_arr(response, "\"items\"", room->items, 32);
	if (room->item_count < 0)
		return (-1);
	return (0);
}

static int	parse_npcs(const char *response, t_room *room)
{
	room->npc_count = extract_arr(response, "\"npcs\"", room->npcs, 32);
	if (room->npc_count < 0)
		return (-1);
	return (0);
}

int	parse_look(const char *response, t_room *room)
{
	const char	*exits;

	if (response == NULL || room == NULL)
		return (-1);
	memset(room, 0, sizeof(*room));
	if (strncmp(response, "OK ", 3) == 0)
		response += 3;
	if (extract_str(response, "\"name\"", room->name, sizeof(room->name)) < 0)
		return (-1);
	if (extract_str(response, "\"description\"", room->description,
			sizeof(room->description)) < 0)
		return (-1);
	exits = strstr(response, "\"exits\"");
	if (exits == NULL)
		return (0);
	extract_str(exits, "\"north\"", room->north, sizeof(room->north));
	extract_str(exits, "\"south\"", room->south, sizeof(room->south));
	extract_str(exits, "\"east\"", room->east, sizeof(room->east));
	extract_str(exits, "\"west\"", room->west, sizeof(room->west));
	if (parse_items(response, room) < 0 || parse_npcs(response, room) < 0)
		return (-1);
	return (0);
}
