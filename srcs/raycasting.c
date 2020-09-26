/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 14:07:28 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/25 11:34:29 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		calc_sidedist(t_mlx *mlx, t_raycast_note *rc)
{
	if (rc->rd_x < 0)
	{
		rc->st_x = -1;
		rc->side_dx = (mlx->prm.px - rc->mx) * rc->delta_dx;
	}
	else
	{
		rc->st_x = 1;
		rc->side_dx = (rc->mx + 1.0 - mlx->prm.px) * rc->delta_dx;
	}
	if (rc->rd_y < 0)
	{
		rc->st_y = -1;
		rc->side_dy = (mlx->prm.py - rc->my) * rc->delta_dy;
	}
	else
	{
		rc->st_y = 1;
		rc->side_dy = (rc->my + 1.0 - mlx->prm.py) * rc->delta_dy;
	}
}

static void		calc_deltadist(t_mlx *mlx, t_raycast_note *rc)
{
	while (rc->hit == 0)
	{
		if (rc->side_dx < rc->side_dy)
		{
			rc->side_dx += rc->delta_dx;
			rc->mx += rc->st_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dy += rc->delta_dy;
			rc->my += rc->st_y;
			rc->side = 1;
		}
		if (mlx->map[rc->my][rc->mx] > '0')
			rc->hit = 1;
	}
}

static void		calc_floor_ceiling(t_mlx *mlx, t_raycast_note *rc, int x)
{
	int y;

	y = 0;
	while (y < rc->draw_start)
	{
		mlx->buf[y][x] = mlx->info.color_c;
		y++;
	}
	y = rc->draw_end;
	while (y < mlx->info.h - 1)
	{
		mlx->buf[y][x] = mlx->info.color_f;
		y++;
	}
}

static void		calc_line_height(t_mlx *mlx, t_raycast_note *rc)
{
	if (rc->side == 0)
		rc->pp_walld = \
				(rc->mx - mlx->prm.px + (1 - rc->st_x) / 2) / rc->rd_x;
	else
		rc->pp_walld = \
				(rc->my - mlx->prm.py + (1 - rc->st_y) / 2) / rc->rd_y;
	rc->line_height = (int)(mlx->info.h / rc->pp_walld);
	rc->draw_start = -rc->line_height / 2 + mlx->info.h / 2;
	rc->draw_end = rc->line_height / 2 + mlx->info.h / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	if (rc->draw_end >= mlx->info.h)
		rc->draw_end = mlx->info.h - 1;
}

void			raycasting(t_mlx *mlx)
{
	t_raycast_note	rc;
	int				idx;

	idx = 0;
	while (idx < mlx->info.w)
	{
		set_raycast_note(&rc, mlx, idx);
		calc_sidedist(mlx, &rc);
		calc_deltadist(mlx, &rc);
		calc_line_height(mlx, &rc);
		calc_floor_ceiling(mlx, &rc, idx);
		calc_wall(mlx, &rc, idx);
		calc_sprite(mlx, &rc, idx);
		idx++;
	}
}
