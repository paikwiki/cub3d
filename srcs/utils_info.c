/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:39:42 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/21 21:27:12 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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

void	check_rgb_range(int value)
{
	if (value > 255 || value < 0)
		exit_puterr("Wrong range of RGB values(0~255)");
}

void	parse_rgb_hexstr_helper(char *rgb_hex, char *temp, int idx)
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
}

char	*parse_rgb_hexstr(int *dest)
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
		parse_rgb_hexstr_helper(rgb_hex, temp, idx);
		idx++;
	}
	free(temp);
	return (rgb_hex);
}

void	get_rgb_int(int *dest, char **raw_values)
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
		check_rgb_range(idx++);
}

int		atoi_hexchar(char chr)
{
	if (chr == 'a' || chr == 'A')
		return (10);
	if (chr == 'b' || chr == 'B')
		return (11);
	if (chr == 'c' || chr == 'C')
		return (12);
	if (chr == 'd' || chr == 'D')
		return (13);
	if (chr == 'e' || chr == 'E')
		return (14);
	if (chr == 'f' || chr == 'F')
		return (15);
	else
		return (chr - 48);
}

int		get_int_value_from_hexstr(char *rgb_hex)
{
	int idx;
	int res;

	idx = 2;
	res = 0;
	while (rgb_hex[idx] != '\0')
		res = (res * 16) + atoi_hexchar(rgb_hex[idx++]);
	return (res);
}

void	get_info_ceil_floor(char *line, t_note *note)
{
	char	*raw_str;
	char	**raw_values;
	int		dest[3];
	char	*rgb_hex;

	raw_str = ft_strndup((char *)&line[2], ft_strlen((const char *)&line[2]));
	raw_values = ft_split(raw_str, ',');
	rgb_hex = NULL;
	get_rgb_int(dest, raw_values);
	rgb_hex = parse_rgb_hexstr(dest);
	if (ft_strncmp((const char *)line, "F ", 2) == 0)
		note->rgb_floor = get_int_value_from_hexstr(rgb_hex);
	else
		note->rgb_ceiling = get_int_value_from_hexstr(rgb_hex);
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
