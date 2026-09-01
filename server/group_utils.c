
#include "mud.h"


t_player	*find_player_by_name(t_world *w, char *name)
{
	int	i;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (w->players[i].fd != -1 && w->players[i].name && \
			strcmp(w->players[i].name, name) == 0)
			return (&w->players[i]);
		i++;
	}
	return (NULL);
}

void	broadcast_group(t_world *w, char *gid, char *msg, int exclude_fd)
{
	int	i;

	if (!gid || !msg)
		return ;
	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (w->players[i].fd != -1 && w->players[i].fd != exclude_fd && \
			w->players[i].group_id && strcmp(w->players[i].group_id, gid) == 0)
			write(w->players[i].fd, msg, strlen(msg));
		i++;
	}
}