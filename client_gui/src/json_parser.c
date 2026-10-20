/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:20:29 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:20:33 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

static const char	*find_json_value(const char *json, const char *key)
{
	const char	*pos;

	pos = strstr(json, key);
	if (pos == NULL)
		return (NULL);
	pos += strlen(key);
	pos = strchr(pos, ':');
	if (pos == NULL)
		return (NULL);
	pos++;
	while (*pos == ' ' || *pos == '\t')
		pos++;
	return (pos);
}

int	extract_str(const char *json, const char *key,
		char *dst, size_t dst_size)
{
	const char	*pos;
	const char	*start;
	const char	*end;
	size_t		len;

	pos = find_json_value(json, key);
	if (pos == NULL || *pos != '"')
		return (-1);
	start = pos + 1;
	end = strchr(start, '"');
	if (end == NULL)
		return (-1);
	len = end - start;
	if (len >= dst_size)
		len = dst_size - 1;
	memcpy(dst, start, len);
	dst[len] = '\0';
	return (0);
}

static int	copy_json_string(const char **pos, char *dst, size_t dst_size)
{
	const char	*start;
	const char	*end;
	size_t		len;

	if (**pos != '"')
		return (-1);
	start = ++(*pos);
	end = strchr(start, '"');
	if (end == NULL)
		return (-1);
	len = end - start;
	if (len >= dst_size)
		len = dst_size - 1;
	memcpy(dst, start, len);
	dst[len] = '\0';
	*pos = end + 1;
	return (0);
}

int	extract_arr(const char *json, const char *key,
		char values[][128], int max_values)
{
	const char	*pos;
	int			count;

	pos = find_json_value(json, key);
	if (pos == NULL)
		return (0);
	if (*pos != '[')
		return (-1);
	pos++;
	count = 0;
	while (*pos && *pos != ']' && count < max_values)
	{
		while (*pos == ' ' || *pos == '\t' || *pos == ',')
			pos++;
		if (*pos == ']')
			break ;
		if (copy_json_string(&pos, values[count], 128) < 0)
			return (-1);
		count++;
	}
	return (count);
}

int	extract_int(const char *json, const char *key, int *value)
{
	const char	*pos;

	pos = find_json_value(json, key);
	if (pos == NULL)
		return (-1);
	*value = atoi(pos);
	return (0);
}
