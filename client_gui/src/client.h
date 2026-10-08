#ifndef GUI_H
# define GUI_H

#include "../../shared/protocol.h"
#define BUFFER_SIZE 1024

typedef struct s_scene t_scene;

struct s_scene {
    void (*update)(t_scene *scene);
    void (*draw)(t_scene *scene);
    void (*destroy)(t_scene *scene);
};

typedef struct s_client {
    int socket;
    int connected;
    char recv_buffer[BUFFER_SIZE];
} t_client;

void client_init(t_client *client);
int client_connect(t_client *client, const char *ip, int port);
int client_send(t_client *client, const char *message);
int client_receive(t_client *client, char *buf, size_t size);
void client_disconnect(t_client *client);

typedef struct s_manager {
    t_scene *current;
    t_client *client;
} t_manager;

void scene_manager_init(t_manager *manager, t_client *client);
void scene_manager_set(t_manager *manager, t_scene *scene);
void scene_manager_update(t_manager *manager);
void scene_manager_draw(t_manager *manager);
void scene_manager_destroy(t_manager *manager);

#endif
