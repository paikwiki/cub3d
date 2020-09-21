/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:37:29 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/18 16:38:01 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	put_map(char **map, t_note *note)
{
	int	idx;

	idx = 0;
	while (idx < note->map_height)
	{
		ft_putstr("$");
		ft_putstr(map[idx++]);
		ft_putstr("$\n");
	}
}
