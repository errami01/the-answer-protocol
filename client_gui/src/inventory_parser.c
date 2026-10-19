#include "inventory.h"

static const char	*skip_inventory_separators(const char *pos)
{
	while (*pos == ' ' || *pos == '\t' || *pos == ',')
		pos++;
	return (pos);
}

static int	parse_inventory_item(const char **pos, char **dst)
{
	const char	*start;
	const char	*end;
	size_t		len;

	if (**pos != '"')
		return (-1);
	start = ++(*pos);
	end = strchr(start, '"');
	if (!end)
		return (-1);
	len = end - start;
	*dst = malloc(len + 1);
	if (!*dst)
		return (-1);
	memcpy(*dst, start, len);
	(*dst)[len] = '\0';
	*pos = end + 1;
	return (0);
}

int	move_pos(const char **pos, int *count, const char *response)
{
	*pos = strchr(response, '[');
	if (!*pos)
		return (-1);
	(*pos)++;
	*count = 0;
	return (0);
}

int	parse_inventory(const char *response, t_game *game)
{
	const char	*pos;
	int			count;

	if (!response || !game)
		return (-1);
	clear_inventory(game);
	if (strncmp(response, "OK ", 3) == 0)
		response += 3;
	if (move_pos(&pos, &count, response) == -1)
		return (-1);
	while (*pos && *pos != ']' && count < MAX_INVENTORY)
	{
		pos = skip_inventory_separators(pos);
		if (*pos == ']')
			break ;
		if (parse_inventory_item(&pos, &game->inventory[count]) < 0)
		{
			clear_inventory(game);
			return (-1);
		}
		count++;
	}
	game->inventory[count] = NULL;
	return (0);
}
