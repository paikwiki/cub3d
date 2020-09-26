/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:12:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/26 19:46:52 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			draw(t_mlx *mlx)
{
	int	y;
	int x;

	y = 0;
	while (y < mlx->info.h)
	{
		x = 0;
		while (x < mlx->info.w)
		{
			mlx->img.data[y * mlx->info.w + x] = mlx->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
}

static int		main_loop(t_mlx *mlx)
{
	raycasting(mlx);
	draw(mlx);
	return (0);
}

void			load_image(t_mlx *mlx, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->ptr = mlx_xpm_file_to_image(mlx->ptr, \
			path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->ptr, \
			&img->bpp, &img->size_line, &img->endian);
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(mlx->ptr, img->ptr);
}

void			load_texture(t_mlx *mlx)
{
	t_img	img;

	load_image(mlx, mlx->texture[1], mlx->info.tex_no, &img);
	load_image(mlx, mlx->texture[2], mlx->info.tex_ea, &img);
	load_image(mlx, mlx->texture[3], mlx->info.tex_so, &img);
	load_image(mlx, mlx->texture[4], mlx->info.tex_we, &img);
	load_image(mlx, mlx->texture[5], mlx->info.tex_s, &img);
}

int				main(int argc, char **argv)
{
	t_mlx	*mlx;
	t_note	note;
	t_list	*lines;

	if (argc < 2)
		ft_exit_puterr("Map does not exist.\n");
	init_note(&note);
	lines = NULL;
	read_cub_file(argv[1], &note, &lines);
	if (note.is_map == FALSE)
		ft_exit_puterr("Fail to get information of map.");
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	process_map(mlx, &note, &lines);
	free(lines);
	init_mlx(mlx, &note);
	printf("sprites: %d\n", (int)(ft_lstsize(note.sprites)));
	load_texture(mlx);
	mlx->img.ptr = mlx_new_image(mlx->ptr, mlx->info.w, mlx->info.h);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr, \
			&mlx->img.bpp, &mlx->img.size_line, &mlx->img.endian);
	mlx_hook(mlx->win, X_EVENT_KEY_EXIT, 0, &ft_exit, mlx);
	mlx_hook(mlx->win, X_EVENT_KEY_PRESS, 0, &handle_key, mlx);
	mlx_loop_hook(mlx->ptr, &main_loop, mlx);
	mlx_loop(mlx->ptr);
	return (0);
}
