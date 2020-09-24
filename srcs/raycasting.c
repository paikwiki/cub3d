/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 14:07:28 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/24 18:30:47 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_raycast_note(t_raycast_note *rc, t_mlx *mlx, int idx)
{
	rc->cam_x = 2 * idx / (double)mlx->info.w - 1;
	rc->rd_x = mlx->prm.dx + mlx->prm.pln_x * rc->cam_x;
	rc->rd_y = mlx->prm.dy + mlx->prm.pln_y * rc->cam_x;
	rc->mx = (int)mlx->prm.px;
	rc->my = (int)mlx->prm.py;
	rc->side_dx = 0;
	rc->side_dy = 0;
	rc->delta_dx = fabs(1 / rc->rd_x);
	rc->delta_dy = fabs(1 / rc->rd_y);
	rc->pp_walld = 0;
	rc->st_x = 0;
	rc->st_y = 0;
	rc->hit = 0;
	rc->side = 0;
	rc->color = 0x0000FF;
	rc->line_height = 0;
	rc->draw_start = 0;
	rc->draw_end = 0;
}

void		raycasting(t_mlx *mlx)
{
	t_raycast_note	rc;
	int				idx;

	idx = 0;
	while (idx < mlx->info.w)
	{
		set_raycast_note(&rc, mlx, idx);
		if (rc.rd_x < 0)
		{
			rc.st_x = -1;
			rc.side_dx = (mlx->prm.px - rc.mx) * rc.delta_dx;
		}
		else
		{
			rc.st_x = 1;
			rc.side_dx = (rc.mx + 1.0 - mlx->prm.px) * rc.delta_dx;
		}
		if (rc.rd_y < 0)
		{
			rc.st_y = -1;
			rc.side_dy = (mlx->prm.py - rc.my) * rc.delta_dy;
		}
		else
		{
			rc.st_y = 1;
			rc.side_dy = (rc.my + 1.0 - mlx->prm.py) * rc.delta_dy;
		}
		while (rc.hit == 0)
		{
			if (rc.side_dx < rc.side_dy)
			{
				rc.side_dx += rc.delta_dx;
				rc.mx += rc.st_x;
				rc.side = 0;
			}
			else
			{
				rc.side_dy += rc.delta_dy;
				rc.my += rc.st_y;
				rc.side = 1;
			}
			if (mlx->map[rc.my][rc.mx] > '0')
				rc.hit = 1;
		}
		if (rc.side == 0)
			rc.pp_walld = (rc.mx - mlx->prm.px + (1 - rc.st_x) / 2) / rc.rd_x;
		else
			rc.pp_walld = (rc.my - mlx->prm.py + (1 - rc.st_y) / 2) / rc.rd_y;
		rc.line_height = (int)(mlx->info.h / rc.pp_walld);
		rc.draw_start = -rc.line_height / 2 + mlx->info.h / 2;
		rc.draw_end = rc.line_height / 2 + mlx->info.h / 2;
		if (rc.draw_start < 0)
			rc.draw_start = 0;
		if (rc.draw_end >= mlx->info.h)
			rc.draw_end = mlx->info.h - 1;
		if (rc.side == 1)
			rc.color = rc.color / 2;
		ver_line(mlx, idx, rc.draw_start, rc.draw_end, rc.color);
//		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
		idx++;
	}
}

void		draw_floor_ceiling(t_mlx *mlx)
{
	int		cnt_w;
	int		cnt_h;

	cnt_h = -1;
	while (++cnt_h < (mlx->info.h / 2) && (cnt_w = -1) == -1)
		while (++cnt_w < mlx->info.w)
			mlx->img.data[cnt_h * mlx->info.w + cnt_w] = mlx->info.color_c;
	cnt_h = (mlx->info.h / 2) - 1;
	while (++cnt_h < mlx->info.h && (cnt_w = -1) == -1)
		while (++cnt_w < mlx->info.w)
			mlx->img.data[cnt_h * mlx->info.w + cnt_w] = mlx->info.color_f;
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
}
