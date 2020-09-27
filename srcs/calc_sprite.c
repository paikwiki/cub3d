/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 22:40:00 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/27 03:07:24 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void 	sort_sprite_by_dist(t_mlx *mlx)
{
	int			idx;
	int			end;
	t_sprite	*temp_sprite;

	end = mlx->info.cnt_sprite;
	while (end > 0)
	{
		idx = 0;
		while (idx < end - 1)
		{
			if (mlx->info.sprites[idx]->distance < mlx->info.sprites[idx + 1]->distance)
			{
				temp_sprite = mlx->info.sprites[idx];
				mlx->info.sprites[idx] = mlx->info.sprites[idx + 1];
				mlx->info.sprites[idx + 1] = temp_sprite;
			}
			idx++;
		}
		end--;
	}
}

void 	calc_sprite(t_mlx *mlx)
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
		idx_sprite++;
	}
}
