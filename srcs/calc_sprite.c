/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 20:22:03 by cbaek             #+#    #+#             */
/*   Updated: 2020/10/02 23:04:23 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_sprite_px(t_game *game, t_sprite_note *sp)
{
	int stripe;
	int y;

	stripe = sp->draw_start_x;
	while (stripe < sp->draw_end_x)
	{
		sp->tex_x = (int)((256 * (stripe - (-sp->sprite_w / 2 + \
				sp->sprite_screen_x)) * TEX_WIDTH / sp->sprite_w) / 256);
		if (sp->trns_y > 0 && stripe > 0 && stripe < game->info.w && \
				sp->trns_y < game->info.z_buffer[stripe])
		{
			y = sp->draw_start_y;
			while (y < sp->draw_end_y)
			{
				sp->d = (y) * 256 - game->info.h * 128 + sp->sprite_h * 128;
				sp->tex_y = ((sp->d * TEX_HEIGHT) / sp->sprite_h) / 256;
				sp->color = game->texture[4][TEX_WIDTH * sp->tex_y + sp->tex_x];
				if ((sp->color & 0x00FFFFFF) != 0)
					game->buf[y][stripe] = sp->color;
				y++;
			}
		}
		stripe++;
	}
}

static void	calc_sprite_w_h(t_game *game, t_sprite_note *sp)
{
	sp->sprite_h = (int)fabs((game->info.h / sp->trns_y));
	sp->draw_start_y = -sp->sprite_h / 2 + game->info.h / 2;
	if (sp->draw_start_y < 0)
		sp->draw_start_y = 0;
	sp->draw_end_y = sp->sprite_h / 2 + game->info.h / 2;
	if (sp->draw_end_y >= game->info.h)
		sp->draw_end_y = game->info.h - 1;
	sp->sprite_w = (int)fabs((game->info.h / sp->trns_y));
	sp->draw_start_x = -sp->sprite_w / 2 + sp->sprite_screen_x;
	if (sp->draw_start_x < 0)
		sp->draw_start_x = 0;
	sp->draw_end_x = sp->sprite_w / 2 + sp->sprite_screen_x;
	if (sp->draw_end_x >= game->info.w)
		sp->draw_end_x = game->info.w - 1;
}

static void	init_sp_note(t_sprite_note *sp)
{
	sp->spr_x = 0;
	sp->spr_y = 0;
	sp->inv_det = 0;
	sp->trns_x = 0;
	sp->trns_y = 0;
	sp->sprite_screen_x = 0;
	sp->sprite_w = 0;
	sp->sprite_h = 0;
	sp->draw_start_x = 0;
	sp->draw_end_x = 0;
	sp->draw_start_y = 0;
	sp->draw_end_y = 0;
	sp->tex_x = 0;
	sp->tex_y = 0;
	sp->d = 0;
	sp->color = 0;
}

void		calc_sprite(t_game *game)
{
	int				idx;
	t_sprite_note	sp;

	init_sp_note(&sp);
	idx = 0;
	while (idx < game->info.cnt_sprite)
	{
		if (game->info.sprites[idx])
		{
			sp.spr_x = game->info.sprites[idx]->x - game->prm.px;
			sp.spr_y = game->info.sprites[idx]->y - game->prm.py;
		}
		sp.inv_det = 1.0 / (game->prm.pln_x * game->prm.dy - \
				game->prm.dx * game->prm.pln_y);
		sp.trns_x = sp.inv_det * \
				(game->prm.dy * sp.spr_x - game->prm.dx * sp.spr_y);
		sp.trns_y = sp.inv_det * \
				(-game->prm.pln_y * sp.spr_x + game->prm.pln_x * sp.spr_y);
		sp.sprite_screen_x = (int)((game->info.w / 2) * \
				(1 + sp.trns_x / sp.trns_y));
		calc_sprite_w_h(game, &sp);
		set_sprite_px(game, &sp);
		idx++;
	}
}
