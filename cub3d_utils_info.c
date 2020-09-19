/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:39:42 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/19 22:49:31 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_info_texture(char *line, t_note *note, int idx)
{
	char	*str;

	str = ft_strndup((char *)&line[idx], ft_strlen((const char *)&line[idx]));
	if (ft_strncmp((const char *)line, "NO ", 3) == 0)
		note->info_no = str;
	else if (ft_strncmp((const char *)line, "SO ", 3) == 0)
		note->info_so = str;
	else if (ft_strncmp((const char *)line, "WE ", 3) == 0)
		note->info_we = str;
	else if (ft_strncmp((const char *)line, "EA ", 3) == 0)
		note->info_ea = str;
	else if (ft_strncmp((const char *)line, "S ", 2) == 0)
		note->info_s = str;
}

void	parse_rgb(int *dest, char **raw_values)
{
	int		idx;

	idx = 0;
	while (idx < 3)
	{
		check_isdigit_all(raw_values[idx]);
		dest[idx] = ft_atoi(raw_values[idx]);
		idx++;
	}
	idx = 0;
	while (idx < 3)
	{
		if (dest[idx] > 255 || dest[idx] < 0)
			exit_puterr("Wrong range of RGB values(0~255)");
		idx++;
	}
}

void	get_info_ceil_floor(char *line, t_note *note)
{
	char	*raw_str;
	char	**raw_values;
	int		*dest;

	raw_str = ft_strndup((char *)&line[2], ft_strlen((const char *)&line[2]));
	raw_values = ft_split(raw_str, ',');
	if (ft_strncmp((const char *)line, "F ", 2) == 0)
		dest = note->info_f;
	else
		dest = note->info_c;
	parse_rgb(dest, raw_values);
	free(raw_values[0]);
	free(raw_values[1]);
	free(raw_values[2]);
	free(raw_values);
}

void	get_info_resolution(char *line, t_note *note)
{
	size_t	idx;
	char	*raw_str;
	char	**raw_values;
	int		max_size[2];

	max_size[0] = 1920;
	max_size[1] = 1080;
	raw_str = ft_strndup((char *)&line[2], ft_strlen((const char *)&line[2]));
	raw_values = ft_split(raw_str, ' ');
	idx = 0;
	while (idx < 2)
	{
		check_isdigit_all(raw_values[idx]);
		note->info_r[idx] = ft_atoi(raw_values[idx]);
		note->info_r[idx] = note->info_r[idx] <= max_size[idx] ?
				note->info_r[idx] : max_size[idx];
		idx++;
	}
	free(raw_values[0]);
	free(raw_values[1]);
	free(raw_values);
}

void	generate_info(char *line, t_note *note)
{
	if (ft_strncmp((const char *)line, "R ", 2) == 0)
		get_info_resolution(line, note);
	else if (ft_strncmp((const char *)line, "F ", 2) == 0 ||
			ft_strncmp((const char *)line, "C ", 2) == 0)
		get_info_ceil_floor(line, note);
	else if (ft_strncmp((const char *)line, "S ", 2) == 0)
		get_info_texture(line, note, 2);
	else if (ft_strncmp((const char *)line, "SO ", 3) == 0 ||
			ft_strncmp((const char *)line, "WE ", 3) == 0 ||
			ft_strncmp((const char *)line, "EA ", 3) == 0 ||
			ft_strncmp((const char *)line, "NO ", 3) == 0)
		get_info_texture(line, note, 3);
	note->is_map = count_info(note) < 8 ? FALSE : TRUE;
}
