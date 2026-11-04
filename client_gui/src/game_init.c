#include "game_init.h"
#include "game_utils.h"
#include "notification.h"

int	init_room(t_game *game, const char *look_init)
{
	t_room	*room;

	room = malloc(sizeof(*room));
	if (!room)
	{
		show_notification(game, "Something went wrong.");
		return (0);
	}
	if (parse_look(look_init, room) < 0)
	{
		show_notification(game, "Something went wrong.");
		return (0);
	}
	game->current = room;
	return (1);
}

void	init_chat(t_game *game)
{
	game->chat_count = 0;
	memset(game->chat, 0, sizeof(game->chat));
}

void	init_players(t_game *game)
{
	game->players_open = 0;
	game->room_player_count = 0;
	game->server_player_count = 0;
}
