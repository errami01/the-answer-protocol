/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quests.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:22:25 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:22:26 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUESTS_H
# define QUESTS_H

# include <raylib.h>

typedef struct s_quest
{
	char	id[128];
	char	status[64];
}	t_quest;

#endif
