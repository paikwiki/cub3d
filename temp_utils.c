/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:37:29 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/23 16:20:08 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void	ver_line(t_mlx *mlx, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(mlx->ptr, mlx->win, x, y, color);
		y++;
	}
}

void	put_map(char **map)
{
	int	idx;

	idx = 0;
	while (map[idx] != 0 && ft_strlen(map[idx]) > 0)
	{
		ft_putstr("$");
		ft_putstr(map[idx]);
		ft_putstr("$\n");
		idx++;
	}
}
