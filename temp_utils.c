/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:37:29 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/23 16:20:08 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void	put_map(char **map)
{
	int	idx;

	idx = 0;
	while (map[idx] != 0 && ft_strlen(map[idx]) > 0)
	{
		ft_putstr("$");
		ft_putstr(map[idx]);
		ft_putstr("$\n");
		idx++;
	}
}
