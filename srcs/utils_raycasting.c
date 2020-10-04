/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:32:22 by cbaek             #+#    #+#             */
/*   Updated: 2020/10/02 23:05:13 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** we: rc->side == 0 && rc->rd_x < 0
** ea: rc->side == 0
** no: rc->side == 1 && rc->rd_y < 0
** so: rc->side == 1
*/

static int		get_tex_num(t_game *game, t_raycast_note *rc)
{
	int	tex_num;

	if (game->map[rc->my][rc->mx] == '2')
		tex_num = 4;
	else
	{
		if (rc->side == 0 && rc->rd_x < 0)
			tex_num = 3;
		else if (rc->side == 0)
			tex_num = 1;
		if (rc->side == 1 && rc->rd_y < 0)
			tex_num = 0;
		else if (rc->side == 1)
			tex_num = 2;
	}
	return (tex_num);
}

static void		proc_calc_wall(t_game *game, t_raycast_note *rc, \
		int win_x, int tex_x)
{
	int		tex_num;
	double	step;
	double	tex_pos;
	int		win_y;
	int		tex_y;

	tex_num = get_tex_num(game, rc);
	step = 1.0 * TEX_HEIGHT / rc->line_height;
	tex_pos = (rc->draw_start - game->info.h / 2 + rc->line_height / 2) * step;
	win_y = rc->draw_start;
	while (win_y < rc->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		game->buf[win_y][win_x] = \
				game->texture[tex_num][TEX_HEIGHT * tex_y + tex_x];
		if (rc->side == 0)
			game->buf[win_y][win_x] = (game->buf[win_y][win_x] >> 1) & 7829367;
		win_y++;
	}
}

void			calc_wall(t_game *game, t_raycast_note *rc, int idx)
{
	double	wall_x;
	int		tex_x;

	if (rc->side == 0)
		wall_x = game->prm.py + rc->pp_walld * rc->rd_y;
	else
		wall_x = game->prm.px + rc->pp_walld * rc->rd_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEX_WIDTH);
	if (rc->side == 0 && rc->rd_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (rc->side == 1 && rc->rd_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	proc_calc_wall(game, rc, idx, tex_x);
}

void			set_raycast_note(t_raycast_note *rc, t_game *game, int idx)
{
	rc->cam_x = 2 * idx / (double)game->info.w - 1;
	rc->rd_x = game->prm.dx + game->prm.pln_x * rc->cam_x;
	rc->rd_y = game->prm.dy + game->prm.pln_y * rc->cam_x;
	rc->mx = (int)game->prm.px;
	rc->my = (int)game->prm.py;
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
