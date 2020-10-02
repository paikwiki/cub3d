/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:34:43 by cbaek             #+#    #+#             */
/*   Updated: 2020/10/02 23:04:59 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_done_map(t_note *note)
{
	if (note->is_map == FALSE)
		ft_exit_puterr("Fail to get information of map.");
	return ;
}

static void	process_read_cub_file(int *fd, t_note *note, t_list **lines)
{
	char	*line;

	while (note->is_done == FALSE)
	{
		if ((note->c_rd = get_next_line(*fd, &line)) == 0)
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

void		read_cub_file(char *file_path, t_note *note, t_list **lines)
{
	int		fd;

	if ((fd = open(file_path, O_RDONLY)) > 0)
		process_read_cub_file(&fd, note, lines);
	else
		ft_exit_puterr("Fail to open a map file.");
	check_done_map(note);
}
