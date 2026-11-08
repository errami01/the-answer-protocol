#include "chat.h"
#include "game.h"
#include "group.h"
#include "players.h"
#include "json_parser.h"

static void	evt_chat(t_game *game, char *buf)
{
	char	message[128];

	if (strncmp(buf, "EVT ROOM CHAT ", 14) == 0)
	{
		snprintf(message, sizeof(message), "[ROOM] %s", buf + 14);
		add_chat_message(game, message);
	}
	else if (strncmp(buf, "EVT GLOBAL CHAT ", 16) == 0)
	{
		snprintf(message, sizeof(message), "[GLOBAL] %s", buf + 16);
		add_chat_message(game, message);
	}
}

static void	evt_players(t_game *game, char *buf)
{
	char	*stats;

	stats = strstr(buf, "EVT STATS");
	if (stats)
		extract_int(stats + 18, "server", &game->server_player_count);
	if (strncmp(buf, "EVT ROOM PRESENCE ENTER ", 24) == 0)
		add_player(game, buf + 24);
	else if (strncmp(buf, "EVT ROOM PRESENCE LEAVE ", 24) == 0)
		remove_player(game, buf + 24);
}

static void	evt_group(t_game *game, char *buf)
{
	if (strncmp(buf, "EVT GROUP INVITE ", 17) == 0)
		group_invite_receive(game, buf);
}

static void	evt_items(t_game *game, char *buf)
{
	char	item[128];

	if (strncmp(buf, "EVT ROOM ITEM TAKE", 18) == 0)
	{
		strcpy(item, buf + 19);
		item[strlen(item) - 1] = '\0';
		remove_item(game, item);
	}
	else if (strncmp(buf, "EVT ROOM ITEM DROP", 18) == 0)
	{
		strcpy(item, buf + 19);
		item[strlen(item) - 1] = '\0';
		add_item(game, item);
	}
}

void	dispatch_evt(t_game *game, char *buf)
{
	evt_chat(game, buf);
	evt_players(game, buf);
	evt_group(game, buf);
	evt_items(game, buf);
}
