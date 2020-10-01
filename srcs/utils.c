/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:21:54 by paikwiki          #+#    #+#             */
/*   Updated: 2020/10/02 02:52:47 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_note(t_note *note)
{
	note->c_rd = 0;
	note->is_map = 0;
	note->is_done = 0;
	note->info_r[0] = -1;
	note->info_r[1] = -1;
	note->info_no = 0;
	note->info_so = 0;
	note->info_we = 0;
	note->info_ea = 0;
	note->info_s = 0;
	note->rgb_ceiling = -1;
	note->rgb_floor = -1;
	note->player_xy[0] = -1;
	note->player_xy[1] = -1;
	note->player_dir = ' ';
	note->map_width = 0;
	note->map_height = 0;
	note->sprites = 0;
}

void	check_isdigit_all(char *str)
{
	size_t idx;
	size_t len;

	idx = 0;
	len = ft_strlen(str);
	while (idx < len)
	{
		if (ft_isdigit(str[idx]) == FALSE)
			ft_exit_puterr("Values of RGB or resolution are must be digit.");
		idx++;
	}
}

void	ft_putstr(char *str)
{
	int idx;

	if (!str)
		return ;
	idx = 0;
	while (str[idx] != 0)
		write(1, &str[idx++], 1);
}

int		ft_exit(int exit_val)
{
	exit(exit_val);
	return (exit_val);
}

void	ft_exit_puterr(const char *msg)
{
	ft_putstr((char *)"Error:\n");
	ft_putstr((char *)msg);
	ft_putstr((char *)"\n");
	exit(EXIT_FAILURE);
}
