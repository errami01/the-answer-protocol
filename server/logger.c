/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 21:37:35 by aberrami          #+#    #+#             */
/*   Updated: 2026/08/27 22:01:11 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mud.h"
#include <time.h>
void	log_event(const char *level, const char *player, const char *action)
{
	FILE	*fp;
	char	timestamp[64];
	time_t	now;

	now = time(NULL);
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%SZ", gmtime(&now));
	fp = fopen("server.log", "a");
	if (fp)
	{
		fprintf(fp, "{\"time\": \"%s\", \"level\": \"%s\", \"user\": \"%s\", \"msg\": \"%s\"}\n",
			timestamp, level, player, action);
		fclose(fp);
	}
}