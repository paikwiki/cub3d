/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:31:10 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/24 18:30:47 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		get_wall_char(char **map, int x_start, int y_start)
{
	if (map[y_start][x_start] == ' ')
		return (-1);
	else if (map[y_start][x_start] == '1')
		return (y_start);
	else
		exit_puterr("Check the outer wall.");
	return (0);
}

void	check_mapline_horizon(char **map, int xs, int xe, int y)
{
	int		start;
	int		end;

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
	int		start;
	int		end;

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

void	check_map_horizon(char **map, t_note *note)
{
	int		x_start;
	int		y_start;
	int		mapline_start;
	int		mapline_end;

	y_start = 0;
	while (y_start < note->map_height)
	{
		x_start = 0;
		mapline_start = -1;
		mapline_end = -1;
		while (x_start < note->map_width && mapline_start == -1)
			mapline_start = get_wall_char(map, x_start++, y_start);
		x_start = note->map_width - 1;
		while (x_start > 0 && mapline_end == -1)
			mapline_end = get_wall_char(map, x_start--, y_start);
		if (mapline_start != -1)
			check_mapline_horizon(map, mapline_start, mapline_end, y_start);
		y_start++;
	}
}

void	check_map_vertical(char **map, t_note *note)
{
	int		x_start;
	int		y_start;
	int		mapline_start;
	int		mapline_end;

	x_start = 0;
	while (x_start < note->map_width)
	{
		y_start = 0;
		mapline_start = -1;
		mapline_end = -1;
		while (y_start < note->map_height && mapline_start == -1)
			mapline_start = get_wall_char(map, x_start, y_start++);
		y_start = note->map_height - 1;
		while (y_start > 0 && mapline_end == -1)
			mapline_end = get_wall_char(map, x_start, y_start--);
		if (mapline_start != -1)
			check_mapline_vertical(map, mapline_start, mapline_end, x_start);
		x_start++;
	}
}
