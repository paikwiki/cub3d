/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 20:22:03 by paikwiki          #+#    #+#             */
/*   Updated: 2020/10/01 20:22:03 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calc_sprite(t_game *game)
{
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