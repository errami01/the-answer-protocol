/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msturma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:20:36 by msturma           #+#    #+#             */
/*   Updated: 2026/10/20 11:20:36 by msturma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_PARSER_H
# define JSON_PARSER_H

# include <stdlib.h>
# include <string.h>

int	extract_str(const char *json, const char *key, char *dst, size_t dst_size);
int	extract_arr(const char *json, const char *key,
		char values[][128], int max_values);
int	extract_int(const char *json, const char *key, int *value);

#endif
