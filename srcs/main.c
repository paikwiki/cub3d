/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:12:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/28 18:53:43 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			draw(t_game *game)
{
	int	y;
	int x;

	y = 0;
	while (y < game->info.h)
	{
		x = 0;
		while (x < game->info.w)
		{
			game->img.data[y * game->info.w + x] = game->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->ptr, game->win, game->img.ptr, 0, 0);
}

static int		main_loop(t_game *game)
{
	raycasting(game);
	draw(game);
	return (0);
}

void			load_image(t_game *game, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->ptr = mlx_xpm_file_to_image(game->ptr, \
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
	mlx_destroy_image(game->ptr, img->ptr);
}

void			load_texture(t_game *mlx)
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
	t_game	*game;
	t_note	note;
	t_list	*lines;

	if (argc < 2)
		ft_exit_puterr("Map does not exist.\n");
	init_note(&note);
	lines = NULL;
	read_cub_file(argv[1], &note, &lines);
	if (note.is_map == FALSE)
		ft_exit_puterr("Fail to get information of map.");
	if((game = (t_game *)malloc(sizeof(t_game))) == 0)
		return (0);
	process_map(game, &note, &lines);
	free(lines);
	init_game(game, &note);
	load_texture(game);
	game->img.ptr = mlx_new_image(game->ptr, game->info.w, game->info.h);
	game->img.data = (int *)mlx_get_data_addr(game->img.ptr, \
			&game->img.bpp, &game->img.size_line, &game->img.endian);
	mlx_hook(game->win, X_EVENT_KEY_EXIT, 0, &ft_exit, game);
	mlx_hook(game->win, X_EVENT_KEY_PRESS, 0, &handle_key, game);
	mlx_loop_hook(game->ptr, &main_loop, game);
	mlx_loop(game->ptr);
	return (0);
}
