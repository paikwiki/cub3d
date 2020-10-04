/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:17:09 by cbaek             #+#    #+#             */
/*   Updated: 2020/10/02 23:14:11 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/*
** rotate_player()
** counterclockwise direction: -1;
** clockwise direction: 1;
*/

static void	rotate_player(t_game *game, int dir)
{
	double	dx_old;
	double	pln_x_old;

	dx_old = game->prm.dx;
	game->prm.dx = game->prm.dx * cos(dir * game->prm.r_spd) \
			- game->prm.dy * sin(dir * game->prm.r_spd);
	game->prm.dy = dx_old * sin(dir * game->prm.r_spd) \
			+ game->prm.dy * cos(dir * game->prm.r_spd);
	pln_x_old = game->prm.pln_x;
	game->prm.pln_x = game->prm.pln_x * cos(dir * game->prm.r_spd) \
			- game->prm.pln_y * sin(dir * game->prm.r_spd);
	game->prm.pln_y = pln_x_old * sin(dir * game->prm.r_spd) \
			+ game->prm.pln_y * cos(dir * game->prm.r_spd);
}

/*
** move_player_front_back()
** W - front direction: 1;
** S - back direction: -1;
*/

static void	move_player_front_back(t_game *game, int dir)
{
	double mv_x;
	double mv_y;

	mv_x = game->prm.dx * game->prm.m_spd;
	mv_y = game->prm.dy * game->prm.m_spd;
	if (game->map[(int)(game->prm.py)][(int)(game->prm.px + (dir * mv_x))] \
			!= '1')
		game->prm.px += (dir * mv_x);
	if (game->map[(int)(game->prm.py + (dir * mv_y))][(int)(game->prm.px)] \
			!= '1')
		game->prm.py += (dir * mv_y);
}

/*
** move_player_left_right()
** A - left direction: -1;
** D - right direction: 1;
*/

static void	move_player_left_right(t_game *game, int dir)
{
	double mv_x;
	double mv_y;

	mv_x = game->prm.pln_x * game->prm.m_spd;
	mv_y = game->prm.pln_y * game->prm.m_spd;
	if (game->map[(int)(game->prm.py)][(int)(game->prm.px + (dir * mv_x))] \
			!= '1')
		game->prm.px += (dir * mv_x);
	if (game->map[(int)(game->prm.py + (dir * mv_y))][(int)(game->prm.px)] \
			!= '1')
		game->prm.py += (dir * mv_y);
}

int			handle_key(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		move_player_front_back(game, 1);
	if (keycode == KEY_S || keycode == KEY_DN)
		move_player_front_back(game, -1);
	if (keycode == KEY_A)
		move_player_left_right(game, -1);
	if (keycode == KEY_D)
		move_player_left_right(game, 1);
	if (keycode == KEY_RA)
		rotate_player(game, 1);
	if (keycode == KEY_LA)
		rotate_player(game, -1);
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}
