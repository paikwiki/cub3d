/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 17:04:17 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/26 21:13:55 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	generate_info_sprite_pos(t_note *note, char **map, int x, int y)
{
	t_sprite *sprite;

	if (!map)
		ft_exit_puterr("sprite error");
	if ((sprite = (t_sprite *)malloc(sizeof(t_sprite))) == 0)
		return ;
	sprite->x = x + 0.5;
	sprite->y = y + 0.5;
	sprite->distance = -1;
	if (!note->sprites)
		note->sprites = ft_lstnew(sprite);
	else
		ft_lstadd_back(&note->sprites, ft_lstnew(sprite));
}
