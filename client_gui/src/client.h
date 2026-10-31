/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:18:20 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:18:22 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "../../shared/protocol.h"

# define BUFFER_SIZE 1024
# define MAX_COMMANDS 64
# define MAX_COMMAND_SIZE 512
# define COMMAND_INTERVAL 0.25

typedef struct s_scene	t_scene;

struct		s_scene
{
	void	(*update)(t_scene *scene);
	void	(*draw)(t_scene *scene);
	void	(*destroy)(t_scene *scene);
};

typedef struct s_client
{
	int		socket;
	int		connected;
	char	recv_buffer[BUFFER_SIZE];

	char	pending[MAX_COMMANDS][MAX_COMMAND_SIZE];
	int		pending_count;

	double	last_send_time;
}		t_client;

void	client_init(t_client *client);
int		client_connect(t_client *client, const char *ip, int port);
int		client_send(t_client *client, const char *message);
int		client_receive(t_client *client, char *buf, size_t size);
void	client_disconnect(t_client *client);
void	client_update(t_client *client);

typedef struct s_manager
{
	t_scene		*current;
	t_client	*client;

	char		*ip;
	int			port;
}		t_manager;

void	scene_manager_init(t_manager *manager, t_client *client,
			char *ip, int port);
void	scene_manager_set(t_manager *manager, t_scene *scene);
void	scene_manager_update(t_manager *manager);
void	scene_manager_draw(t_manager *manager);
void	scene_manager_destroy(t_manager *manager);

#endif
