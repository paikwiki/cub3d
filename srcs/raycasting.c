/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 14:07:28 by cbaek             #+#    #+#             */
/*   Updated: 2020/10/03 00:05:17 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		calc_sidedist(t_game *game, t_raycast_note *rc)
{
	if (rc->rd_x < 0)
	{
		rc->st_x = -1;
		rc->side_dx = (game->prm.px - rc->mx) * rc->delta_dx;
	}
	else
	{
		rc->st_x = 1;
		rc->side_dx = (rc->mx + 1.0 - game->prm.px) * rc->delta_dx;
	}
	if (rc->rd_y < 0)
	{
		rc->st_y = -1;
		rc->side_dy = (game->prm.py - rc->my) * rc->delta_dy;
	}
	else
	{
		rc->st_y = 1;
		rc->side_dy = (rc->my + 1.0 - game->prm.py) * rc->delta_dy;
	}
}

static void		calc_deltadist(t_game *game, t_raycast_note *rc)
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
		if (game->map[rc->my][rc->mx] > '0')
			rc->hit = 1;
	}
}

static void		calc_floor_ceiling(t_game *game, t_raycast_note *rc, int x)
{
	int y;

	y = 0;
	while (y < rc->draw_start)
	{
		game->buf[y][x] = game->info.color_c;
		y++;
	}
	y = rc->draw_end;
	while (y >= 0 && y < game->info.h - 1)
	{
		game->buf[y][x] = game->info.color_f;
		y++;
	}
}

static void		calc_line_height(t_game *game, t_raycast_note *rc)
{
	if (rc->side == 0)
		rc->pp_walld = \
				(rc->mx - game->prm.px + (1 - rc->st_x) / 2) / rc->rd_x;
	else
		rc->pp_walld = \
				(rc->my - game->prm.py + (1 - rc->st_y) / 2) / rc->rd_y;
	rc->line_height = (int)(game->info.h / rc->pp_walld);
	rc->draw_start = -rc->line_height / 2 + game->info.h / 2;
	rc->draw_end = rc->line_height / 2 + game->info.h / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	if (rc->draw_end >= game->info.h)
		rc->draw_end = game->info.h - 1;
}

void			raycasting(t_game *game)
{
	t_raycast_note	rc;
	int				idx;

	idx = 0;
	while (idx < game->info.w)
	{
		set_raycast_note(&rc, game, idx);
		calc_sidedist(game, &rc);
		calc_deltadist(game, &rc);
		calc_line_height(game, &rc);
		calc_floor_ceiling(game, &rc, idx);
		calc_wall(game, &rc, idx);
		game->info.z_buffer[idx] = rc.pp_walld;
		idx++;
	}
	get_sprite(game);
	sort_sprite_by_dist(game);
	calc_sprite(game);
}
