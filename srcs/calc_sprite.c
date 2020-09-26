/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 22:40:00 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/26 23:42:48 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void 	sort_sprite_by_dist(t_mlx *mlx)
{
	int idx;
	int end;

	t_sprite *temp_sprite;

	if ((temp_sprite = (t_sprite *)malloc(sizeof(t_sprite))) == 0) ////////////
		return ;

	end = mlx->info.cnt_sprite;
	while (end > 0)
	{
		idx = 0;
		while (idx < end - 1)
		{
			if (mlx->info.sprites[idx]->distance > mlx->info.sprites[idx + 1]->distance)
			{
				temp_sprite = mlx->info.sprites[idx];
				mlx->info.sprites[idx] = mlx->info.sprites[idx + 1];
				mlx->info.sprites[idx + 1] = temp_sprite;
			}
			idx++;
		}
		end--;
//		printf("info.sprites[0]->distance: %f\n", mlx->info.sprites[0]->distance);
//		printf("info.sprites[1]->distance: %f\n", mlx->info.sprites[1]->distance);
//		printf("info.sprites[2]->distance: %f\n", mlx->info.sprites[2]->distance);
//		printf("info.sprites[3]->distance: %f\n", mlx->info.sprites[3]->distance);
	}
//	free(temp_sprite);
}

void 	calc_sprite(t_mlx *mlx, t_raycast_note *rc, int idx)
{
	int	idx_sprite;

	idx_sprite = 0;
	while(idx_sprite < mlx->info.cnt_sprite)
	{
		mlx->info.sprites[idx_sprite]->distance = \
				sqrt(((mlx->info.sprites[idx_sprite]->x - mlx->prm.px) * \
				(mlx->info.sprites[idx_sprite]->x - mlx->prm.px)) + \
				((mlx->info.sprites[idx_sprite]->y - mlx->prm.py) * \
				(mlx->info.sprites[idx_sprite]->y - mlx->prm.py)));
//		printf("player x, y: %f, %f\n", \
//			   mlx->prm.px, mlx->prm.py);
//		printf("sprite x, y: %f, %f\n", \
//			   mlx->info.sprites[idx_sprite]->x, mlx->info.sprites[idx_sprite]->y);
//		printf("info.sprites[%d]->dist: %f\n", \
//			   idx_sprite, mlx->info.sprites[idx_sprite]->distance);
		idx_sprite++;
	}

	sort_sprite_by_dist(mlx);
	if (!mlx || !rc || idx < 0)
		ft_exit_puterr("test");
}
