/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:53:45 by cbaek             #+#    #+#             */
/*   Updated: 2020/10/02 23:14:26 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	set_player_dir(t_game *game, t_note *note)
{
	game->prm.dx = 0;
	game->prm.dy = -1;
	game->prm.pln_x = 0.66;
	game->prm.pln_y = 0;
	if (note->player_dir == 'S')
	{
		game->prm.dy = 1;
		game->prm.pln_x = -0.66;
	}
	else if (note->player_dir == 'W')
	{
		game->prm.dx = -1;
		game->prm.dy = 0;
		game->prm.pln_x = 0;
		game->prm.pln_y = -0.66;
	}
	else if (note->player_dir == 'E')
	{
		game->prm.dx = 1;
		game->prm.dy = 0;
		game->prm.pln_x = 0;
		game->prm.pln_y = 0.66;
	}
}

static void	init_info(t_game *game, t_note *note)
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
	game->info.sprites = 0;
	game->info.z_buffer = (double *)ft_calloc(note->info_r[0], sizeof(double));
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
	game->info.sprites = \
			(t_sprite **)ft_calloc(game->info.cnt_sprite, sizeof(t_sprite *));
	crr_item = note->sprites;
	idx = 0;
	while (idx < game->info.cnt_sprite)
	{
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
