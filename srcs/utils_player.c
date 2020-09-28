/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 23:02:26 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/25 14:15:51 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_player_dir(t_game *game, t_note *note)
{
	game->prm.dx = 0;
	game->prm.dy = -1;
	game->prm.pln_x = 0.66;
	game->prm.pln_y = 0;
	if (note->player_dir == 'S')
	{
		game->prm.dy = 1;
		game->prm.pln_x = -0.66;
	}
	else if (note->player_dir == 'W')
	{
		game->prm.dx = -1;
		game->prm.dy = 0;
		game->prm.pln_x = 0;
		game->prm.pln_y = -0.66;
	}
	else if (note->player_dir == 'E')
	{
		game->prm.dx = 1;
		game->prm.dy = 0;
		game->prm.pln_x = 0;
		game->prm.pln_y = 0.66;
	}
}

int		is_player_pos(char chr)
{
	if (ft_strchr("NSWE", chr) == 0)
		return (FALSE);
	return (TRUE);
}

void	generate_info_p_pos(t_note *note, char **map, int x, int y)
{
	if (note->player_dir == ' ')
	{
		note->player_xy[0] = x;
		note->player_xy[1] = y;
		note->player_dir = map[y][x];
	}
	else
		ft_exit_puterr("Map error. player position is more than one.");
}
