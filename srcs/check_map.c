/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:31:10 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/24 20:54:00 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		check_mapline_horizon(char **map, int xs, int xe, int y)
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
				ft_exit_puterr("check_mapline_horizon : Wrong map");
		}
		start++;
	}
}

static void		check_mapline_vertical(char **map, int ys, int ye, int x)
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
				ft_exit_puterr("check_mapline_vertical : Wrong map");
		}
		start++;
	}
}

static void		check_map_horizon(char **map, t_note *note)
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

static void		check_map_vertical(char **map, t_note *note)
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

void			check_map(char **map, t_note *note)
{
	check_map_horizon(map, note);
	check_map_vertical(map, note);
}
