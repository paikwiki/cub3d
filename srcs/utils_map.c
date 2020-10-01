/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:36:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/10/01 21:40:54 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		is_player_pos(char chr)
{
	if (ft_strchr("NSWE", chr) == 0)
		return (FALSE);
	return (TRUE);
}

int		is_sprite_pos(char chr)
{
	if (chr == '2')
		return (TRUE);
	return (FALSE);
}

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
