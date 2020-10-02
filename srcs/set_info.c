/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:39:42 by cbaek             #+#    #+#             */
/*   Updated: 2020/10/02 23:05:02 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_no_space(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == ' ')
			ft_exit_puterr("Map error. Check info.");
		idx++;
	}
}

static void	get_info_texture(char *line, t_note *note, int idx)
{
	char	*str;

	str = ft_strndup((char *)&line[idx], ft_strlen((const char *)&line[idx]));
	check_no_space(str);
	if (ft_strncmp((const char *)line, "NO ", 3) == 0 && note->info_no == 0)
		note->info_no = str;
	else if (ft_strncmp((const char *)line, "SO ", 3) == 0 && \
			note->info_so == 0)
		note->info_so = str;
	else if (ft_strncmp((const char *)line, "WE ", 3) == 0 && \
			note->info_we == 0)
		note->info_we = str;
	else if (ft_strncmp((const char *)line, "EA ", 3) == 0 && \
			note->info_ea == 0)
		note->info_ea = str;
	else if (ft_strncmp((const char *)line, "S ", 2) == 0 && \
			note->info_s == 0)
		note->info_s = str;
	else
		ft_exit_puterr("Map error. Check info.");
}

static void	check_rawstr_resolution(char *raw_str)
{
	int idx;
	int flag;

	flag = 0;
	idx = 0;
	while (raw_str[idx] != '\0')
	{
		if (raw_str[idx] == ' ')
			flag++;
		if (flag > 1)
			ft_exit_puterr("Map error. Check resolution info.");
		idx++;
	}
	if (flag == 0)
		ft_exit_puterr("Map error. Check resolution info.");
}

static void	get_info_resolution(char *line, t_note *note)
{
	size_t	idx;
	char	*raw_str;
	char	**raw_values;
	int		max_size[2];

	max_size[0] = 1920;
	max_size[1] = 1080;
	raw_str = ft_strndup((char *)&line[2], ft_strlen((const char *)&line[2]));
	check_rawstr_resolution(raw_str);
	raw_values = ft_split(raw_str, ' ');
	free(raw_str);
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

void		set_info(char *line, t_note *note)
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
	free(line);
	note->is_map = count_info(note) < 8 ? FALSE : TRUE;
}
