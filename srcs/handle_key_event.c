/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:17:09 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/24 13:17:09 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

/*
** rotate_player()
** counterclockwise direction: -1;
** clockwise direction: 1;
*/

static void	rotate_player(t_mlx *mlx, int dir)
{
	double	dx_old;
	double	pln_x_old;

	dx_old = mlx->prm.dx;
	mlx->prm.dx = mlx->prm.dx * cos(dir * mlx->prm.r_spd) \
					- mlx->prm.dy * sin(dir * mlx->prm.r_spd);
	mlx->prm.dy = dx_old * sin(dir * mlx->prm.r_spd) \
					+ mlx->prm.dy * cos(dir * mlx->prm.r_spd);
	pln_x_old = mlx->prm.pln_x;
	mlx->prm.pln_x = mlx->prm.pln_x * cos(dir * mlx->prm.r_spd) \
					- mlx->prm.pln_y * sin(dir * mlx->prm.r_spd);
	mlx->prm.pln_y = pln_x_old * sin(dir * mlx->prm.r_spd) \
					+ mlx->prm.pln_y * cos(dir * mlx->prm.r_spd);
}

/*
** move_player_front_back()
** W - front direction: 1;
** S - back direction: -1;
 */

static void	move_player_front_back(t_mlx *mlx, int dir)
{
	double mv_x;
	double mv_y;

	mv_x = mlx->prm.dx * mlx->prm.m_spd;
	mv_y = mlx->prm.dy * mlx->prm.m_spd;
	if (mlx->map[(int)(mlx->prm.py)][(int)(mlx->prm.px + (dir * mv_x))] != '1')
		mlx->prm.px += (dir * mv_x);
	if (mlx->map[(int)(mlx->prm.py + (dir * mv_y))][(int)(mlx->prm.px)] != '1')
		mlx->prm.py += (dir * mv_y);
}

/*
** move_player_left_right()
** A - left direction: -1;
** D - right direction: 1;
*/

static void	move_player_left_right(t_mlx *mlx, int dir)
{
	double mv_x;
	double mv_y;

	mv_x = mlx->prm.pln_x * mlx->prm.m_spd;
	mv_y = mlx->prm.pln_y * mlx->prm.m_spd;
	if (mlx->map[(int)(mlx->prm.py)][(int)(mlx->prm.px + (dir * mv_x))] != '1')
		mlx->prm.px += (dir * mv_x);
	if (mlx->map[(int)(mlx->prm.py + (dir * mv_y))][(int)(mlx->prm.px)] != '1')
		mlx->prm.py += (dir * mv_y);
}

int     key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		move_player_front_back(mlx, 1);
	if (keycode == KEY_S || keycode == KEY_DN)
		move_player_front_back(mlx, -1);
	if (keycode == KEY_A)
		move_player_left_right(mlx, -1);
	if (keycode == KEY_D)
		move_player_left_right(mlx, 1);
	if (keycode == KEY_RA)
		rotate_player(mlx, 1);
	if (keycode == KEY_LA)
		rotate_player(mlx, -1);
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}
