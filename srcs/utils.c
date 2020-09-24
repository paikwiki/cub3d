/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:21:54 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/24 21:27:33 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	exit(EXIT_FAILURE);
}
