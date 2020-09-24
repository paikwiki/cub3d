/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:21:54 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/24 13:55:37 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int		count_info(t_note *note)
{
	int	cnt;

	cnt = 0;
	if (note->info_r[1] != -1)
		cnt++;
	if (note->info_no != 0)
		cnt++;
	if (note->info_so != 0)
		cnt++;
	if (note->info_we != 0)
		cnt++;
	if (note->info_ea != 0)
		cnt++;
	if (note->info_s != 0)
		cnt++;
	if (note->rgb_floor != -1)
		cnt++;
	if (note->rgb_ceiling != -1)
		cnt++;
	return (cnt);
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

void	check_isdigit_all(char *str)
{
	size_t idx;
	size_t len;

	idx = 0;
	len = ft_strlen(str);
	while (idx < len)
	{
		if (ft_isdigit(str[idx]) == FALSE)
			exit_puterr("Values of RGB or resolution are must be digit.");
		idx++;
	}
}


int		ft_exit(int exit_val)
{
	exit(exit_val);
	return (exit_val);
}

void	exit_puterr(const char *msg)
{
	ft_putstr((char *)"Error:\n");
	ft_putstr((char *)msg);
	exit(EXIT_FAILURE);
}
