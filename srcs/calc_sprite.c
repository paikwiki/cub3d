/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 22:40:00 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/29 16:09:03 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void 	sort_sprite_by_dist(t_game *game)
{
	int			idx;
	int			end;
	t_sprite	*temp_sprite;

	end = game->info.cnt_sprite;
	while (end > 0)
	{
		idx = 0;
		while (idx < end - 1)
		{
			if (game->info.sprites[idx] && game->info.sprites[idx + 1])
			{
				if (game->info.sprites[idx]->distance < game->info.sprites[idx + 1]->distance)
				{
					temp_sprite = game->info.sprites[idx];
					game->info.sprites[idx] = game->info.sprites[idx + 1];
					game->info.sprites[idx + 1] = temp_sprite;
				}
			}
			idx++;
		}
		end--;
	}
}

void 	calc_sprite(t_game *game)
{
	int	idx_sprite;

	idx_sprite = 0;
	while(idx_sprite < game->info.cnt_sprite)
	{
		if (game->info.sprites[idx_sprite])
		{
			game->info.sprites[idx_sprite]->distance = \
				sqrt(((game->info.sprites[idx_sprite]->x - game->prm.px) * \
				(game->info.sprites[idx_sprite]->x - game->prm.px)) + \
				((game->info.sprites[idx_sprite]->y - game->prm.py) * \
				(game->info.sprites[idx_sprite]->y - game->prm.py)));
		}
		idx_sprite++;
	}
}
