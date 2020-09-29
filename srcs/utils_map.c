/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:36:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/29 20:08:30 by paikwiki         ###   ########.fr       */
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

char	check_valid_map_char(char chr)
{
	if (ft_strchr(" 012NSWE", chr) == 0)
		ft_exit_puterr("Not valid char.");
	return (chr);
}

int 	is_sprite_pos(char chr)
{
	if (chr == '2')
		return TRUE;
	return FALSE;
}

void	set_map(char **map, t_note *note, t_list **lines)
{
	int		idx;
	int		idx_map;
//	t_list	*crr_item;
//	char	*line;

	idx_map = -1;
	while (++idx_map > -1)
	{
//		crr_item = *lines;
//		line = (*lines)->content;
		idx = 0;
		while (((char *)(*lines)->content)[idx] != '\0')
		{
			map[idx_map][idx] = check_valid_map_char(((char *)(*lines)->content)[idx]);
			if (is_sprite_pos(map[idx_map][idx]) == TRUE)
			{
				generate_info_sprite_pos(note, map, idx, idx_map);
				map[idx_map][idx] = '0';
			}
			else if (is_player_pos(map[idx_map][idx]) == TRUE)
			{
				generate_info_p_pos(note, map, idx, idx_map);
				map[idx_map][idx] = '0';
			}
			idx++;
		}
		free((*lines)->content);
		(*lines)->content = 0;
		if ((*lines)->next == 0)
			return ;
//		free(*lines);
		lines = &(*lines)->next;
	}
//	free(crr_item);

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
				generate_info(line, note);
//			free(line);
		}
		note->map_height = ft_lstsize(*lines);
//		free(line);
	}
	else
		ft_exit_puterr("Fail to open a map file.");
}
