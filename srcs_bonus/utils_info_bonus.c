/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_info_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:12:39 by cbaek             #+#    #+#             */
/*   Updated: 2020/10/02 23:15:07 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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

int		char_to_hexadecimal(char chr)
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
		ft_exit_puterr("Wrong range of RGB values(0~255)");
}
