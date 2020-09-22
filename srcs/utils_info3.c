/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_info3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:12:39 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/22 11:13:09 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int		atoi_hexchar(char chr)
{
	if (chr == 'a' || chr == 'A')
		return (10);
	if (chr == 'b' || chr == 'B')
		return (11);
	if (chr == 'c' || chr == 'C')
		return (12);
	if (chr == 'd' || chr == 'D')
		return (13);
	if (chr == 'e' || chr == 'E')
		return (14);
	if (chr == 'f' || chr == 'F')
		return (15);
	else
		return (chr - 48);
}

void	check_rgb_range(int value)
{
	if (value > 255 || value < 0)
		exit_puterr("Wrong range of RGB values(0~255)");
}
