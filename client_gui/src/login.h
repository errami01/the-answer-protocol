#ifndef LOGIN_H
# define LOGIN_H

#include "client.h"

typedef enum e_login_state {
    LOGIN_IDLE,
    LOGIN_WAIT_HELLO,
    LOGIN_WAIT_CONNECTED,
    LOGIN_WAIT_LOOK,
    LOGIN_SUCCESS,
    LOGIN_ERROR,
} t_login_state;

typedef struct s_login {
    t_scene base;
    t_manager *manager;
    char username[64];
    int username_len;
    int input_active;
    t_login_state state;
    char error[128];
} t_login;

t_scene *login_create(t_manager *manager);

#endif
