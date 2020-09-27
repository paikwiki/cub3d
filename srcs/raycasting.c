/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 14:07:28 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/27 03:04:58 by paikwiki         ###   ########.fr       */
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
		mlx->info.z_buffer[idx] = rc.pp_walld;
		calc_sprite(mlx);
		sort_sprite_by_dist(mlx);
		idx++;
	}

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
	for(int i = 0; i < mlx->info.cnt_sprite; i++)
	{
		//translate sprite position to relative to camera
		spriteX = mlx->info.sprites[i]->x - mlx->prm.px;
		spriteY = mlx->info.sprites[i]->y - mlx->prm.py;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                          s             [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]
		invDet = 1.0 / (mlx->prm.pln_x * mlx->prm.dy - mlx->prm.dx * mlx->prm.pln_y); //required for correct matrix multiplication

		transformX = invDet * (mlx->prm.dy * spriteX - mlx->prm.dx * spriteY);
		transformY = invDet * (-mlx->prm.pln_y * spriteX + mlx->prm.pln_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		spriteScreenX = (int)((mlx->info.w / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		spriteHeight = (int)fabs((mlx->info.h / transformY)); //using "transformY" instead of the real distance prevents fisheye

		drawStartY = -spriteHeight / 2 + mlx->info.h / 2;
		if(drawStartY < 0) drawStartY = 0;
		drawEndY = spriteHeight / 2 + mlx->info.h / 2;
		if(drawEndY >= mlx->info.h) drawEndY = mlx->info.h - 1;

		//calculate width of the sprite
		spriteWidth = (int)fabs((mlx->info.h / transformY));
		drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= mlx->info.w) drawEndX = mlx->info.w - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_WIDTH / spriteWidth) / 256);

			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < mlx->info.w && transformY < mlx->info.z_buffer[stripe])
				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
//						d = (y-vMoveScreen) * 256 - mlx->info.h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					d = (y) * 256 - mlx->info.h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					texY = ((d * TEX_HEIGHT) / spriteHeight) / 256;
					color = mlx->texture[5][TEX_WIDTH * texY + texX]; //get current color from the texture
					if((color & 0x00FFFFFF) != 0) mlx->buf[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
				}
		}
	}
}
