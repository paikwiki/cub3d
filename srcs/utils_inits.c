/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:53:45 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/29 16:53:13 by paikwiki         ###   ########.fr       */
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

static void	init_texture(t_game *game)
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
	game->info.cnt_sprite = note->sprites == 0 ? 0 : ft_lstsize(note->sprites);
//	if ((game->info.sprites = (t_sprite **)malloc((sizeof(t_sprite *) * game->info.cnt_sprite))) == 0)
//		return ;
//	if ((game->info.z_buffer = (double *)malloc(sizeof(double) * note->info_r[0])) == 0)
//		return ;
	game->info.sprites = 0;
	game->info.z_buffer = (double *)ft_calloc(note->info_r[0], sizeof(double));
	note->info_no = 0;
	free(note->info_no);
	note->info_so = 0;
	free(note->info_so);
	note->info_ea = 0;
	free(note->info_ea);
	note->info_we = 0;
	free(note->info_we);
	note->info_s = 0;
	free(note->info_s);
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

	game->info.sprites = (t_sprite **)ft_calloc(game->info.cnt_sprite, sizeof(t_sprite *));

	crr_item = note->sprites;
	idx = 0;
	while (idx < game->info.cnt_sprite)
	{
		game->info.sprites[idx] = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
		game->info.sprites[idx] = crr_item->content;
		crr_item = (t_list *)crr_item->next;
		idx++;
	}
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->info.w, \
								game->info.h, "cub3D");
	game->img.img_ptr = mlx_new_image(game->mlx, game->info.w, game->info.h);
	game->img.data = (int *)mlx_get_data_addr(game->img.img_ptr, \
			&game->img.bpp, &game->img.size_line, &game->img.endian);
	init_texture_buffer(game);
	init_texture(game);
}

void		init_map(t_game *game, t_note *note)
{
	int		idx;
	int		idx_sub;

//	if((game->map = (char **)malloc(sizeof(char *) * note->map_height)) == 0)
//		return;
	game->map = (char **)calloc(note->map_height, sizeof(char *));
	idx = 0;
	while (idx < note->map_height)
	{
//		if((game->map[idx] = (char *)malloc(sizeof(char) * note->map_width  + 1)) == 0)
//			return;
		game->map[idx] = (char *)calloc(note->map_width + 1, sizeof(char *));
		game->map[idx][note->map_width] = '\0';
		idx_sub = 0;
		while (idx_sub < note->map_width)
			game->map[idx][idx_sub++] = ' ';
		idx++;
	}
}
