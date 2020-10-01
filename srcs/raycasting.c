/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 14:07:28 by paikwiki          #+#    #+#             */
/*   Updated: 2020/10/01 20:16:56 by paikwiki         ###   ########.fr       */
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
	while (y < game->info.h - 1)
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
	calc_sprite(game);
	sort_sprite_by_dist(game);

	// TEMPORARY VARIABLES
	double spriteX;
	double spriteY;
	double invDet;
	double transformX;
	double transformY;
	int spriteScreenX;
	int spriteHeight;
	int drawStartY;
	int drawEndY;
	int spriteWidth;
	int drawStartX;
	int drawEndX;
	int texX;
	int d;
	int texY;
	int color;


	for(int i = 0; i < game->info.cnt_sprite; i++)
	{
		if (game->info.sprites[i])
		{
			spriteX = game->info.sprites[i]->x - game->prm.px;
			spriteY = game->info.sprites[i]->y - game->prm.py;
		}
		invDet = 1.0 / (game->prm.pln_x * game->prm.dy - game->prm.dx * game->prm.pln_y);

		transformX = invDet * (game->prm.dy * spriteX - game->prm.dx * spriteY);
		transformY = invDet * (-game->prm.pln_y * spriteX + game->prm.pln_x * spriteY);
		spriteScreenX = (int)((game->info.w / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		spriteHeight = (int)fabs((game->info.h / transformY));

		drawStartY = -spriteHeight / 2 + game->info.h / 2;
		if(drawStartY < 0) drawStartY = 0;
		drawEndY = spriteHeight / 2 + game->info.h / 2;
		if(drawEndY >= game->info.h) drawEndY = game->info.h - 1;

		//calculate width of the sprite
		spriteWidth = (int)fabs((game->info.h / transformY));
		drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= game->info.w) drawEndX = game->info.w - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_WIDTH / spriteWidth) / 256);
			if(transformY > 0 && stripe > 0 && stripe < game->info.w && transformY < game->info.z_buffer[stripe])
				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					d = (y) * 256 - game->info.h * 128 + spriteHeight * 128;
					texY = ((d * TEX_HEIGHT) / spriteHeight) / 256;
					color = game->texture[4][TEX_WIDTH * texY + texX];
					if((color & 0x00FFFFFF) != 0) game->buf[y][stripe] = color;
				}
		}
	}
}
