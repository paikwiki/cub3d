/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:53:45 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/24 18:30:47 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_map(t_mlx *mlx, t_note *note)
{
	char	*line;
	int		idx;
	int		idx_sub;

	mlx->map = (char **)malloc(sizeof(char *) * note->map_height + 1);
	mlx->map[note->map_height] = 0;
	idx = 0;
	while (idx < note->map_height)
	{
		line = (char *)malloc((sizeof(char) * note->map_width) + 1);
		line[note->map_width] = '\0';
		idx_sub = 0;
		while (idx_sub < note->map_width)
			line[idx_sub++] = ' ';
		mlx->map[idx] = line;
		idx++;
	}
}

void	init_param(t_mlx *mlx, double px, double py)
{
	mlx->prm.px = px + 0.5;
	mlx->prm.py = py + 0.5;
	mlx->prm.dx = 0;
	mlx->prm.dy = -1;
	mlx->prm.m_spd = 0.1;
	mlx->prm.r_spd = 0.1;
	mlx->prm.pln_x = 0.66;
	mlx->prm.pln_y = 0;
}

void	init_mlx(t_mlx *mlx, t_note *note)
{
	init_param(mlx, note->player_xy[0], note->player_xy[1]);
	mlx->info.w = note->info_r[0];
	mlx->info.h = note->info_r[1];
	mlx->info.color_f = note->rgb_floor;
	mlx->info.color_c = note->rgb_ceiling;
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, mlx->info.w, \
								mlx->info.h, "cub3D");
	mlx->img.ptr = mlx_new_image(mlx->ptr, mlx->info.w, mlx->info.h);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr, \
			&mlx->img.bpp, &mlx->img.size_line, &mlx->img.endian);
}

void	init_note(t_note *note)
{
	note->c_rd = 0;
	note->is_map = 0;
	note->is_done = 0;
	note->info_r[0] = -1;
	note->info_r[1] = -1;
	note->info_no = 0;
	note->info_so = 0;
	note->info_we = 0;
	note->info_ea = 0;
	note->info_s = 0;
	note->rgb_ceiling = -1;
	note->rgb_floor = -1;
	note->player_xy[0] = -1;
	note->player_xy[1] = -1;
	note->player_dir = ' ';
	note->map_width = 0;
	note->map_height = 0;
}
