/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:12:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/10/02 20:10:13 by paikwiki         ###   ########.fr       */
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
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
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

	img->img_ptr = mlx_xpm_file_to_image(game->mlx, \
			path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img_ptr, \
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
	free(path);
	mlx_destroy_image(game->mlx, img->img_ptr);
}

void			load_texture(t_game *game)
{
	t_img	img;

	load_image(game, game->texture[0], game->info.tex_no, &img);
	load_image(game, game->texture[1], game->info.tex_ea, &img);
	load_image(game, game->texture[2], game->info.tex_so, &img);
	load_image(game, game->texture[3], game->info.tex_we, &img);
	load_image(game, game->texture[4], game->info.tex_s, &img);
}

int				main(int argc, char **argv)
{
	t_game	*game;
	t_note	note;
	t_list	*lines;

	if (!(argc == 2 || argc == 3))
		ft_exit_puterr("Wrong params: ./cub3D {FILE_PATH} [--save]");
	init_note(&note);
	lines = NULL;
	read_cub_file(argv[1], &note, &lines);
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	process_map(game, &note, &lines);
	free(lines);
	init_game(game, &note);
	load_texture(game);
	game->img.img_ptr = mlx_new_image(game->mlx, game->info.w, game->info.h);
	game->img.data = (int *)mlx_get_data_addr(game->img.img_ptr, \
			&game->img.bpp, &game->img.size_line, &game->img.endian);
	process_screenshot(argc, argv, game);
	mlx_hook(game->win, X_EVENT_KEY_EXIT, 0, &ft_exit, game);
	mlx_hook(game->win, X_EVENT_KEY_PRESS, 0, &handle_key, game);
	mlx_loop_hook(game->mlx, &main_loop, game);
	mlx_loop(game->mlx);
	free(game);
	return (0);
}
