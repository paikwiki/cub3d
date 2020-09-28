/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_ceil_floor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 10:19:27 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/28 19:49:35 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		proc_int_to_hexstring(char *rgb_hex, char *temp, int idx)
{
	if (ft_strlen(temp) == 2)
	{
		rgb_hex[idx * 2 + 2] = temp[0];
		rgb_hex[idx * 2 + 3] = temp[1];
	}
	else
	{
		rgb_hex[idx * 2 + 2] = '0';
		rgb_hex[idx * 2 + 3] = temp[0];
	}
	free(temp);
}

static char		*int_to_hexstring(int *dest)
{
	int		idx;
	char	*temp;
	char	*rgb_hex;

	idx = 0;
	if ((rgb_hex = (char *)malloc((sizeof(char) * 8) + 1)) == 0)
		return (0);
	rgb_hex[8] = '\0';
	rgb_hex[0] = '0';
	rgb_hex[1] = 'x';
	while (idx < 3)
	{
		temp = ft_uitoa_base((unsigned int)dest[idx], HEX_UPPER);
		proc_int_to_hexstring(rgb_hex, temp, idx);
		idx++;
	}
	return (rgb_hex);
}

static int		hexstring_to_int(char *rgb_hex)
{
	int idx;
	int res;

	idx = 2;
	res = 0;
	while (rgb_hex[idx] != '\0')
		res = (res * 16) + char_to_hexadecimal(rgb_hex[idx++]);
	return (res);
}

static void		generate_rgb_to_int(int *dest, char **raw_values)
{
	int		idx;
	int		value;

	idx = 0;
	while (idx < 3)
	{
		check_isdigit_all(raw_values[idx]);
		value = ft_atoi(raw_values[idx]);
		check_rgb_range(value);
		dest[idx] = value;
//		free(raw_values[idx]);
		idx++;
	}
}

void			get_info_ceil_floor(char *line, t_note *note)
{
	char	*raw_str;
	char	**raw_values;
	int		rgb[3];
	char	*rgb_hex;

	raw_str = ft_strndup((char *)&line[2], ft_strlen((const char *)&line[2]));
	raw_values = ft_split(raw_str, ',');
	free(raw_str);
	rgb_hex = NULL;
	generate_rgb_to_int(rgb, raw_values);
	free(raw_values[0]);
	free(raw_values[1]);
	free(raw_values[2]);
	free(raw_values);
	rgb_hex = int_to_hexstring(rgb);
	if (ft_strncmp((const char *)line, "F ", 2) == 0)
		note->rgb_floor = hexstring_to_int(rgb_hex);
	else
		note->rgb_ceiling = hexstring_to_int(rgb_hex);
	free(rgb_hex);
}
