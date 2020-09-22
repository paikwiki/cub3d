/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:12:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/22 22:47:13 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	process_map(char **map, t_note *note, t_list **lines)
{
	init_map(map, note);
	set_map(map, note, lines);
	check_map_horizon(map, note);
	check_map_vertical(map, note);
}

void    param_init(t_mlx *mlx, double posX, double posY)
{
	mlx->param.posX = posX;
	mlx->param.posY = posY;
	mlx->param.dirX = -1;
	mlx->param.dirY = 0;
	mlx->param.moveSpeed = 1.0;
	mlx->param.rotSpeed = 0.3;
	mlx->param.planeX = 0;
	mlx->param.planeY = 0.66;
}

int     key_press(int keycode)
{
	if (keycode == KEY_W)
		write(1, "W_", 2);
	if (keycode == KEY_S)
		write(1, "S_", 2);
	if (keycode == KEY_A)
		write(1, "A_", 2);
	if (keycode == KEY_D)
		write(1, "D_", 2);
	if (keycode == KEY_RA)
		write(1, "RA_", 3);
	if (keycode == KEY_LA)
		write(1, "LA_", 3);
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

void	clear_screen(t_mlx *mlx)
{
	int idx;
	int sub_idx;
	idx = -1;
	while(++idx < 240)
	{
		sub_idx = -1;
		while (++sub_idx < 120)
		{
			mlx->img.data[idx * 120 + sub_idx] = 0;
		}
	}
}

int		main_loop(t_mlx *mlx)
{
	clear_screen(mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	return (0);
}

int		ft_exit(int ret)
{
	exit(ret);
	return (ret);
}

int		main(int argc, char **argv)
{
	t_mlx	*mlx;
	int		cnt_w;
	int 	cnt_h;
	t_note	note;
	t_list	*lines;
	char	**map;

	if (argc < 2)
		exit_puterr("Map does not exist.\n");
	init_note(&note);
	lines = NULL;
	get_map_file(argv[1], &note, &lines);
	if (note.is_map == FALSE)
		exit_puterr("Fail to get information of map_size.");
	map = (char **)malloc(sizeof(char *) * note.map_height + 1);
	map[note.map_height] = 0;
	process_map(map, &note, &lines);
	free(lines);
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	param_init(mlx, note.player_xy[0], note.player_xy[1]);
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, note.info_r[0],
							  note.info_r[1], "cub3D");
	mlx->img.ptr = mlx_new_image(mlx->ptr, note.info_r[0], note.info_r[1]);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr,
											 &mlx->img.bpp, &mlx->img.size_line, &mlx->img.endian);
	cnt_h = -1;
	while (++cnt_h < (note.info_r[1] / 2) && (cnt_w = -1) == -1)
		while (++cnt_w < note.info_r[0])
			mlx->img.data[cnt_h * note.info_r[0] + cnt_w] = note.rgb_ceiling;
	cnt_h = (note.info_r[1] / 2) - 1;
	while (++cnt_h < note.info_r[1] && (cnt_w = -1) == -1)
		while (++cnt_w < note.info_r[0])
			mlx->img.data[cnt_h * note.info_r[0] + cnt_w] = note.rgb_floor;
	mlx_hook(mlx->win, X_EVENT_KEY_EXIT, 0, &ft_exit, &note);
	mlx_hook(mlx->win, X_EVENT_KEY_PRESS, 0, &key_press, &note);
	mlx_loop_hook(mlx->ptr, &main_loop, mlx);
	mlx_loop(mlx->ptr);
	return (0);
}
