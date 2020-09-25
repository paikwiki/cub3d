/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:32:22 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/25 16:17:33 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** we: rc->side == 0 && rc->rd_x < 0
** ea: rc->side == 0
** no: rc->side == 1 && rc->rd_y < 0
** so: rc->side == 1
*/

static char		get_tex_num(t_mlx *mlx, t_raycast_note *rc)
{
	char	tex_num;

	if (mlx->map[rc->my][rc->mx] == '2')
		tex_num = '5';
	else
	{
		if (rc->side == 0 && rc->rd_x < 0)
			tex_num = mlx->map[rc->my][rc->mx] + 3;
		else if (rc->side == 0)
			tex_num = mlx->map[rc->my][rc->mx] + 1;
		if (rc->side == 1 && rc->rd_y < 0)
			tex_num = mlx->map[rc->my][rc->mx];
		else if (rc->side == 1)
			tex_num = mlx->map[rc->my][rc->mx] + 2;
	}
	return (tex_num);
}

static void		proc_calc_wall(t_mlx *mlx, t_raycast_note *rc, \
		int win_x, int tex_x)
{
	char	tex_num;
	double	step;
	double	tex_pos;
	int		win_y;
	int		tex_y;

	tex_num = get_tex_num(mlx, rc);
	step = 1.0 * TEX_HEIGHT / rc->line_height;
	tex_pos = (rc->draw_start - mlx->info.h / 2 + rc->line_height / 2) * step;
	win_y = rc->draw_start;
	while (win_y < rc->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		mlx->buf[win_y][win_x] = \
				mlx->texture[(int)(tex_num - 48)][TEX_HEIGHT * tex_y + tex_x];
		if (rc->side == 0)
			mlx->buf[win_y][win_x] = (mlx->buf[win_y][win_x] >> 1) & 7829367;
		win_y++;
	}
}

void			calc_wall(t_mlx *mlx, t_raycast_note *rc, int idx)
{
	double	wall_x;
	int		tex_x;

	if (rc->side == 0)
		wall_x = mlx->prm.py + rc->pp_walld * rc->rd_y;
	else
		wall_x = mlx->prm.px + rc->pp_walld * rc->rd_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEX_WIDTH);
	if (rc->side == 0 && rc->rd_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (rc->side == 1 && rc->rd_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	proc_calc_wall(mlx, rc, idx, tex_x);
}

void			set_raycast_note(t_raycast_note *rc, t_mlx *mlx, int idx)
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
	rc->line_height = 0;
	rc->draw_start = 0;
	rc->draw_end = 0;
}
