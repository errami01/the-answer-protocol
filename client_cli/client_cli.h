/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cli.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 18:19:15 by aberrami          #+#    #+#             */
/*   Updated: 2026/10/04 20:32:39 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CLI_H
# define CLIENT_CLI_H

# include "../shared/protocol.h"
# define BUFFER_SIZE 1024

void	read_server(int sock_fd);
void	read_keyboard(int sock_fd);

#endif