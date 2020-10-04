/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 19:55:04 by cbaek             #+#    #+#             */
/*   Updated: 2020/10/02 23:05:05 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	check_valid_map_char(char chr)
{
	if (ft_strchr(" 012NSWE", chr) == 0)
		ft_exit_puterr("Not valid char.");
	return (chr);
}

static void	generate_info_sprite(t_note *note, char **map, int x, int y)
{
	t_sprite *sprite;

	sprite = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
	sprite->x = x + 0.5;
	sprite->y = y + 0.5;
	sprite->distance = -1;
	map[y][x] = '0';
	if (!note->sprites)
		note->sprites = ft_lstnew(sprite);
	else
		ft_lstadd_back(&note->sprites, ft_lstnew(sprite));
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
