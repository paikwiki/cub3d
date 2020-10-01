/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 23:02:26 by paikwiki          #+#    #+#             */
/*   Updated: 2020/10/01 19:55:53 by paikwiki         ###   ########.fr       */
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
