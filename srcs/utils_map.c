/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:36:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/10/01 20:00:10 by paikwiki         ###   ########.fr       */
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
		ft_exit_puterr("Check the outer wall.");
	return (0);
}

void	init_map(t_game *game, t_note *note)
{
	int		idx;
	int		idx_sub;

	game->map = (char **)ft_calloc(note->map_height, sizeof(char *));
	idx = 0;
	while (idx < note->map_height)
	{
		game->map[idx] = \
				(char *)ft_calloc(note->map_width + 1, sizeof(char *));
		game->map[idx][note->map_width] = '\0';
		idx_sub = 0;
		while (idx_sub < note->map_width)
			game->map[idx][idx_sub++] = ' ';
		idx++;
	}
}

void	process_map(t_game *game, t_note *note, t_list **lines)
{
	init_map(game, note);
	set_map(game->map, note, lines);
	check_map(game->map, note);
}

void	read_cub_file(char *file_path, t_note *note, t_list **lines)
{
	int		fd;
	char	*line;

	if ((fd = open(file_path, O_RDONLY)) > 0)
	{
		while (note->is_done == FALSE)
		{
			if ((note->c_rd = get_next_line(fd, &line)) == 0)
				note->is_done = TRUE;
			if (note->is_map == TRUE)
			{
				note->map_width = (int)ft_strlen(line) > note->map_width ?
						(int)ft_strlen(line) : note->map_width;
				if (!lines)
					*lines = ft_lstnew(line);
				else
					ft_lstadd_back(lines, ft_lstnew(line));
			}
			else
				set_info(line, note);
		}
		note->map_height = ft_lstsize(*lines);
	}
	else
		ft_exit_puterr("Fail to open a map file.");
}
