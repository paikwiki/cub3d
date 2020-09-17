/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:12:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/17 17:42:49 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_putstr(char *str)
{
	int idx;

	if (!str)
		return ;
	idx = 0;
	while (str[idx] != 0)
		write(1, &str[idx++], 1);
}

void	exit_puterr(const char *msg)
{
	ft_putstr((char *)"Error:\n");
	ft_putstr((char *)msg);
	exit(EXIT_FAILURE);
}

void	init_note(t_note *note)
{
	note->c_rd = 0;
	note->is_map = 0;
	note->is_done = 0;
	note->info_r[0] = -1;
	note->info_r[1] = -1;
	note->info_no = 0;
	note->info_so = 0;
	note->info_we = 0;
	note->info_ea = 0;
	note->info_s = 0;
	note->info_f[0] = -1;
	note->info_f[1] = -1;
	note->info_f[2] = -1;
	note->info_c[0] = -1;
	note->info_c[1] = -1;
	note->info_c[2] = -1;
	note->map_size[0] = 0;
	note->map_size[1] = 0;
}

int		count_info(t_note *note)
{
	int	cnt;

	cnt = 0;
	if (note->info_r[1] != -1)
		cnt++;
	if (note->info_no != 0)
		cnt++;
	if (note->info_so != 0)
		cnt++;
	if (note->info_we != 0)
		cnt++;
	if (note->info_ea != 0)
		cnt++;
	if (note->info_s != 0)
		cnt++;
	if (note->info_f[2] != -1)
		cnt++;
	if (note->info_c[2] != -1)
		cnt++;
	return (cnt);
}

void	get_info_texture(char *line, t_note *note)
{
	char	*str;

	str = ft_strndup((char *)&line[4], ft_strlen((const char *)&line[4]));
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
//	free(str);
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
	dest[0] = ft_atoi(raw_values[0]);
	dest[1] = ft_atoi(raw_values[1]);
	dest[2] = ft_atoi(raw_values[2]);
//	free(raw_str);
	free(raw_values[0]);
	free(raw_values[1]);
	free(raw_values[2]);
	free(raw_values);
}

void	get_info_resolution(char *line, t_note *note)
{
	char	*raw_str;
	char	**raw_values;

	raw_str = ft_strndup((char *)&line[2], ft_strlen((const char *)&line[2]));
	raw_values = ft_split(raw_str, ' ');
	note->info_r[0] = ft_atoi(raw_values[0]);
	note->info_r[1] = ft_atoi(raw_values[1]);
//	free(raw_str);
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
	else if (ft_strncmp((const char *)line, "S ", 2) == 0 ||
			ft_strncmp((const char *)line, "SO ", 3) == 0 ||
			ft_strncmp((const char *)line, "WE ", 3) == 0 ||
			ft_strncmp((const char *)line, "EA ", 3) == 0 ||
			ft_strncmp((const char *)line, "NO ", 3) == 0)
		get_info_texture(line, note);
//	free(line);
	note->is_map = count_info(note) < 8 ? FALSE : TRUE;
}

void	init_map(char **map, t_note *note)
{
	char	*line;
	int		idx;
	int		idx_sub;

	idx = 0;
	while (idx <= note->map_size[1])
	{
		line = (char *)malloc((sizeof(char) * note->map_size[0]) + 1);
		line[note->map_size[0]] = '\0';
		idx_sub = 0;
		while (idx_sub < note->map_size[0])
			line[idx_sub++] = ' ';
		map[idx] = line;
		idx++;
	}
}

void	set_map(char **map, t_list **lines)
{
	int		idx;
	int		idx_map;
	t_list	*crr_item;
	char	*line;

	idx_map = 0;
	while (1)
	{
		crr_item = *lines;
		idx = 0;
		line = crr_item->content;
		while (line[idx] != '\0')
		{
			if (ft_strchr(" 012NSWE", line[idx]) != 0)
				map[idx_map][idx] = line[idx];
			else
				exit_puterr("Not valid char.");
			idx++;
		}
		if ((*lines)->next != 0)
		{
			free((*lines)->content);
			lines = &((crr_item)->next);
		}
		else
			return ;
		idx_map++;
	}
}

void	get_map_file(char *file_path, t_note *note, t_list **lines)
{
	int		fd;
	char	*line;

	if ((fd = open(file_path, O_RDONLY)) > 0)
	{
		while (note->is_done == FALSE)
		{
			if ((note->c_rd = get_next_line(fd, &line)) <= 0)
				note->is_done = TRUE;
			if (note->is_map == TRUE)
			{
				note->map_size[0] = ft_strlen(line) > note->map_size[0] ?
							(int)ft_strlen(line) : note->map_size[0];
				if (!lines)
					*lines = ft_lstnew(line);
				else
					ft_lstadd_back(lines, ft_lstnew(line));
			}
			else
				generate_info(line, note);
		}
		note->map_size[1] = ft_lstsize(*lines);
	}
	else
		exit_puterr("Fail to open a map_size file.");
}

void	put_map(char **map, t_note *note)
{
	int	idx;

	idx = 0;
	while (idx < note->map_size[1])
	{
		ft_putstr("$");
		ft_putstr(map[idx++]);
		ft_putstr("$\n");
	}
}

void	check_mapline_horizon(char **map, int xs, int xe, int y)
{
	int	start;
	int	end;

	start = xs + 1;
	end = xe - 1;
	while (start < end)
	{
		if (map[y][start] == ' ')
		{
			if (map[y][start - 1] == '1' || map[y][start - 1] == ' ' ||
				map[y][start + 1] == '1' || map[y][start + 1] == ' ')
				;
			else
				exit_puterr("check_mapline_horizon : Wrong map");
		}
		start++;
	}
}

void	check_mapline_vertical(char **map, int ys, int ye, int x)
{
	int	start;
	int	end;

	start = ys + 1;
	end = ye - 1;
	while (start < end)
	{
		if (map[start][x] == ' ')
		{
			if (map[start - 1][x] == '1' || map[start - 1][x] == ' ' ||
				map[start + 1][x] == '1' || map[start + 1][x] == ' ')
				;
			else
				exit_puterr("check_mapline_vertical : Wrong map");
		}
		start++;
	}
}

void 	check_map_horizon(char **map, t_note *note)
{

	int		x_start;
	int 	y_start;
	int 	x_end;
	int 	y_end;
	int 	mapline_start;
	int 	mapline_end;

	y_start = 0;
	x_end = note->map_size[0];
	y_end = note->map_size[1];

	while (y_start < y_end)
	{
		x_start = 0;
		mapline_start = -1;
		mapline_end = -1;
		while (x_start < x_end && mapline_start == -1)
		{
			if (map[y_start][x_start] == ' ')
				x_start++;
			else if (map[y_start][x_start] == '1')
				mapline_start = x_start;
			else
				exit_puterr("horizon start wrong");
		}
		x_start = x_end - 1;
		while (x_start > 0 && mapline_end == -1)
		{
			if (map[y_start][x_start] == ' ')
				x_start--;
			else if (map[y_start][x_start] == '1')
				mapline_end = x_start;
			else
				exit_puterr("horizon end wrong");
		}
		if (mapline_start != -1)
			check_mapline_horizon(map, mapline_start, mapline_end, y_start);
		y_start++;
	}
}

void 	check_map_vertical(char **map, t_note *note)
{

	int		x_start;
	int 	y_start;
	int 	x_end;
	int 	y_end;
	int 	mapline_start;
	int 	mapline_end;

	x_start = 0;
	x_end = note->map_size[0];
	y_end = note->map_size[1];

	while (x_start < x_end)
	{
		y_start = 0;
		mapline_start = -1;
		mapline_end = -1;
		while (y_start < y_end && mapline_start == -1)
		{
			if (map[y_start][x_start] == ' ')
				y_start++;
			else if (map[y_start][x_start] == '1')
				mapline_start = y_start;
			else
				exit_puterr("vertical start wrong");
		}
		y_start = y_end - 1;
		while (y_start > 0 && mapline_end == -1)
		{
			if (map[y_start][x_start] == ' ')
				y_start--;
			else if (map[y_start][x_start] == '1')
				mapline_end = y_start;
			else
				exit_puterr("vertical end wrong!!");
		}
		if (mapline_start != -1)
			check_mapline_vertical(map, mapline_start, mapline_end, x_start);
		x_start++;
	}
}

int		main(int argc, char *argv[])
{
	t_note	note;
	t_list	*lines;
	char	**map;

	if (argc < 2)
		exit_puterr("Map does not exist.\n");
	init_note(&note);
	lines = NULL;
	get_map_file(argv[1], &note, &lines);
	if (note.is_map == FALSE)
		exit_puterr("Fail to get information of map_size.");
	map = (char **)malloc(sizeof(char *) * note.map_size[1] + 1);
	map[note.map_size[1]] = 0;
	init_map(map, &note);
	set_map(map, &lines);
	free(lines);
	check_map_horizon(map, &note);
	check_map_vertical(map, &note);
	put_map(map, &note);
	ft_putstr("Good\n");
	return (0);
}
