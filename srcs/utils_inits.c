/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:53:45 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/28 18:53:43 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_texture_buffer(t_game *game)
{
	int	idx;
	int idx_sub;

	if ((game->buf = (int **)malloc(sizeof(int *) * game->info.h)) == 0)
		ft_exit_puterr("Fail to allocate memory for texture buffer");
	idx = 0;
	while (idx < game->info.w)
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

static void	init_texture(t_game *game)
{
	int idx;
	int idx_sub;

	if (!(game->texture = (int **)malloc(sizeof(int *) * 8)))
		ft_exit_puterr("Fail to allocate memory for mlx");
	idx = 0;
	while (idx < 8)
	{
		if (!(game->texture[idx] = (int *)malloc(sizeof(int) * \
				(TEX_HEIGHT * TEX_WIDTH))))
			ft_exit_puterr("Fail to allocate memory for mlx");
		idx++;
	}
	idx = 0;
	while (idx < 8)
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

void		init_info(t_game *game, t_note *note)
{
	game->info.w = note->info_r[0];
	game->info.h = note->info_r[1];
	game->info.color_f = note->rgb_floor;
	game->info.color_c = note->rgb_ceiling;
	game->info.tex_no = note->info_no;
	game->info.tex_so = note->info_so;
	game->info.tex_ea = note->info_ea;
	game->info.tex_we = note->info_we;
	game->info.tex_s = note->info_s;
	game->info.cnt_sprite = ft_lstsize(note->sprites);
	if ((game->info.sprites = (t_sprite **)malloc((sizeof(t_sprite *) * game->info.cnt_sprite))) == 0)
		return ;
	if ((game->info.z_buffer = (double *)malloc(sizeof(double) * note->info_r[0])) == 0)
		return ;
}

static void	init_param(t_game *game, t_note *note)
{
	game->prm.px = note->player_xy[0] + 0.5;
	game->prm.py = note->player_xy[1] + 0.5;
	game->prm.m_spd = 0.1;
	game->prm.r_spd = 0.1;
	set_player_dir(game, note);
}

void		init_game(t_game *game, t_note *note)
{
	int		idx;
	t_list	*crr_item;

	init_param(game, note);
	init_info(game, note);
	idx = 0;
	crr_item = note->sprites;
	while (idx < game->info.cnt_sprite)
	{
		if ((game->info.sprites[idx] = (t_sprite *)malloc(sizeof(t_sprite))) == 0)
			return;
		game->info.sprites[idx] = crr_item->content;
		crr_item = (t_list *)crr_item->next;
		idx++;
	}
//	free(note->sprites);
//	printf("info.sprites[0]->x,y: %f,%f\n",
//			(double)mlx->info.sprites[0]->x, (double)mlx->info.sprites[0]->y);
//	printf("info.sprites[1]->x,y: %f,%f\n",
//		   (double)mlx->info.sprites[1]->x, (double)mlx->info.sprites[1]->y);
//	printf("info.sprites[2]->x,y: %f,%f\n",
//		   (double)mlx->info.sprites[2]->x, (double)mlx->info.sprites[2]->y);
//	printf("info.sprites[3]->x,y: %f,%f\n",
//		   (double)mlx->info.sprites[3]->x, (double)mlx->info.sprites[3]->y);
	game->ptr = mlx_init();
	game->win = mlx_new_window(game->ptr, game->info.w, \
								game->info.h, "cub3D");
	game->img.ptr = mlx_new_image(game->ptr, game->info.w, game->info.h);
	game->img.data = (int *)mlx_get_data_addr(game->img.ptr, \
			&game->img.bpp, &game->img.size_line, &game->img.endian);
	init_texture_buffer(game);
	init_texture(game);
}

void		init_map(t_game *game, t_note *note)
{
	char	*line;
	int		idx;
	int		idx_sub;

	if((game->map = (char **)malloc(sizeof(char *) * note->map_height + 1)) == 0)
		return;
	game->map[note->map_height] = 0;
	idx = 0;
	while (idx < note->map_height)
	{
		if((line = (char *)malloc((sizeof(char) * note->map_width) + 1)) == 0)
			return;
		line[note->map_width] = '\0';
		idx_sub = 0;
		while (idx_sub < note->map_width)
			line[idx_sub++] = ' ';
		game->map[idx] = line;
		idx++;
	}
	free(line);
}
