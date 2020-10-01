/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 19:55:04 by paikwiki          #+#    #+#             */
/*   Updated: 2020/10/01 20:09:42 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	check_valid_map_char(char chr)
{
	if (ft_strchr(" 012NSWE", chr) == 0)
		ft_exit_puterr("Not valid char.");
	return (chr);
}

static int	is_player_pos(char chr)
{
	if (ft_strchr("NSWE", chr) == 0)
		return (FALSE);
	return (TRUE);
}

static int	is_sprite_pos(char chr)
{
	if (chr == '2')
		return (TRUE);
	return (FALSE);
}

static void	generate_info_p_pos(t_note *note, char **map, int x, int y)
{
	if (note->player_dir == ' ')
	{
		note->player_xy[0] = x;
		note->player_xy[1] = y;
		note->player_dir = map[y][x];
		map[y][x] = '0';
	}
	else
		ft_exit_puterr("Map error. player position is more than one.");
}

void		set_map(char **map, t_note *note, t_list **lines)
{
	int		x;
	int		y;
	t_list	*temp_item;

	y = -1;
	while (++y > -1)
	{
		x = 0;
		while (((char *)(*lines)->content)[x] != '\0')
		{
			map[y][x] = check_valid_map_char(((char *)(*lines)->content)[x]);
			if (is_sprite_pos(map[y][x]) == TRUE)
				generate_info_sprite(note, map, x, y);
			else if (is_player_pos(map[y][x]) == TRUE)
				generate_info_p_pos(note, map, x, y);
			x++;
		}
		free((*lines)->content);
		(*lines)->content = 0;
		if ((*lines)->next == 0)
			return ;
		temp_item = (*lines)->next;
		free(*lines);
		*lines = temp_item;
	}
}
