/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:50:16 by paikwiki          #+#    #+#             */
/*   Updated: 2020/10/01 22:51:11 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_texture_buffer(t_game *game)
{
	int	idx;
	int idx_sub;

	if ((game->buf = (int **)malloc(sizeof(int *) * game->info.h)) == 0)
		ft_exit_puterr("Fail to allocate memory for texture buffer");
	idx = 0;
	while (idx < game->info.h)
	{
		if ((game->buf[idx] = (int *)malloc(sizeof(int) * game->info.w)) == 0)
			ft_exit_puterr("Fail to allocate memory for texture buffer");
		idx++;
	}
	idx = 0;
	while (idx < game->info.h)
	{
		idx_sub = 0;
		while (idx_sub < game->info.w)
		{
			game->buf[idx][idx_sub] = 0;
			idx_sub++;
		}
		idx++;
	}
}

void	init_texture(t_game *game)
{
	int idx;
	int idx_sub;

	if (!(game->texture = (int **)malloc(sizeof(int *) * 5)))
		ft_exit_puterr("Fail to allocate memory for mlx");
	idx = 0;
	while (idx < 5)
	{
		if (!(game->texture[idx] = (int *)malloc(sizeof(int) * \
				(TEX_HEIGHT * TEX_WIDTH))))
			ft_exit_puterr("Fail to allocate memory for mlx");
		idx++;
	}
	idx = 0;
	while (idx < 5)
	{
		idx_sub = 0;
		while (idx_sub < TEX_HEIGHT * TEX_WIDTH)
		{
			game->texture[idx][idx_sub] = 0;
			idx_sub++;
		}
		idx++;
	}
}