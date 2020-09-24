/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_map2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:36:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/24 18:30:47 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	check_valid_map_char(char chr)
{
	if (ft_strchr(" 012NSWE", chr) == 0)
		exit_puterr("Not valid char.");
	return (chr);
}

void	set_map(char **map, t_note *note, t_list **lines)
{
	int		idx;
	int		idx_map;
	t_list	*crr_item;
	char	*line;

	idx_map = -1;
	while (++idx_map > -1)
	{
		crr_item = *lines;
		idx = 0;
		line = crr_item->content;
		while (line[idx] != '\0')
		{
			map[idx_map][idx] = check_valid_map_char(line[idx]);
			if (is_player_pos(map[idx_map][idx++]) == TRUE)
			{
				get_info_player_pos(note, map, idx - 1, idx_map);
				map[idx_map][idx - 1] = '0';
			}
		}
		if ((*lines)->next == 0)
			return ;
		free((*lines)->content);
		lines = &((crr_item)->next);
	}
}

void	process_map(t_mlx *mlx, t_note *note, t_list **lines)
{
	init_map(mlx, note);
	set_map(mlx->map, note, lines);
	check_map_horizon(mlx->map, note);
	check_map_vertical(mlx->map, note);
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
				note->map_width = (int)ft_strlen(line) > note->map_width ?
						(int)ft_strlen(line) : note->map_width;
				if (!lines)
					*lines = ft_lstnew(line);
				else
					ft_lstadd_back(lines, ft_lstnew(line));
			}
			else
				generate_info(line, note);
		}
		note->map_height = ft_lstsize(*lines);
	}
	else
		exit_puterr("Fail to open a map file.");
}
