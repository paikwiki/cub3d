/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 23:02:26 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/24 18:30:47 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		is_player_pos(char chr)
{
	if (ft_strchr("NSWE", chr) == 0)
		return (FALSE);
	return (TRUE);
}

void	get_info_player_pos(t_note *note, char **map, int x, int y)
{
	note->player_xy[0] = x;
	note->player_xy[1] = y;
	note->player_dir = map[y][x];
}
