/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   login.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:20:52 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:20:52 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGIN_H
# define LOGIN_H

# define INPUT_WIDTH 300
# define INPUT_HEIGHT 40
# define BUTTON_WIDTH 120
# define BUTTON_HEIGHT 40
# define SPACING 20

# include "client.h"
# include <raylib.h>

typedef enum e_login_state
{
	LOGIN_IDLE,
	LOGIN_WAIT_HELLO,
	LOGIN_WAIT_CONNECTED,
	LOGIN_WAIT_LOOK,
	LOGIN_SUCCESS,
	LOGIN_ERROR,
}	t_login_state;

typedef struct s_login
{
	t_scene			base;
	t_manager		*manager;
	char			username[64];
	int				username_len;
	int				input_active;
	t_login_state	state;
	char			error[128];
}	t_login;

t_scene		*login_create(t_manager *manager);
void		login_draw(t_scene *scene);
void		login_update(t_scene *scene);
void		handle_username_input(t_login *login);
void		login_submit(t_login *login);
void		draw_login_error(t_login *login);

#endif
