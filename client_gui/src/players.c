#include "players.h"
#include "notification.h"

void	players(t_game *game)
{
	if (game->state != GAME_IDLE)
		return ;
	if (client_send(game->manager->client, "WHO\n") < 0)
	{
		show_notification(game, "Something went wrong.");
		return ;
	}
	game->players_open = 1;
	game->state = GAME_WAIT_WHO;
}

static int	parse_player_name(t_game *game, const char **pos)
{
	char	*name;
	int		i;

	if (**pos != '"')
		return (-1);
	(*pos)++;
	name = game->room_players[game->room_player_count];
	i = 0;
	while (**pos && **pos != '"')
	{
		if (i >= MAX_PLAYER_NAME - 1 || **pos == '\\')
			return (-1);
		name[i++] = *(*pos)++;
	}
	if (**pos != '"')
		return (-1);
	name[i] = '\0';
	(*pos)++;
	game->room_player_count++;
	return (0);
}

static int	parse_room_players(t_game *game, const char *pos)
{
	pos = strchr(pos, '[');
	if (!pos)
		return (-1);
	pos++;
	game->room_player_count = 0;
	while (*pos)
	{
		while (isspace((unsigned char)*pos))
			pos++;
		if (*pos == ']')
			return (0);
		if (game->room_player_count >= MAX_ROOM_PLAYERS)
			return (-1);
		if (parse_player_name(game, &pos) < 0)
			return (-1);
		while (isspace((unsigned char)*pos))
			pos++;
		if (*pos == ',')
			pos++;
		else if (*pos != ']')
			return (-1);
	}
	return (-1);
}

int	parse_who(t_game *game, const char *buf)
{
	const char	*room;
	const char	*server;
	char		*end;
	long		count;

	if (strncmp(buf, "OK ", 3) != 0)
		return (-1);
	room = strstr(buf, "\"room\"");
	server = strstr(buf, "\"server\"");
	if (!room || !server)
		return (-1);
	room = strchr(room, ':');
	server = strchr(server, ':');
	if (!room || !server)
		return (-1);
	if (parse_room_players(game, room + 1) < 0)
		return (-1);
	count = strtol(server + 1, &end, 10);
	if (end == server + 1 || count < 0 || count > 2147483647L)
		return (-1);
	game->server_player_count = (int)count;
	return (0);
}

void	wait_who(t_game *game, char *buf)
{
	if (game->state != GAME_WAIT_WHO)
		return ;
	if (parse_who(game, buf) < 0)
	{
		show_notification(game, "Failed to load players");
		game->players_open = false;
	}
	game->state = GAME_IDLE;
}
