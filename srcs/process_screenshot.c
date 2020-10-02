/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_screenshot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 02:26:56 by cbaek             #+#    #+#             */
/*   Updated: 2020/10/02 23:04:54 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** offeset
**	2	"BM"
**	4	size
**	4	reserved
**	4	array offset
**	4	x size
**	4	y size
**	4	num of color plane (1)
**	2	bit per pixel
**	4
**	4
**	4
**	4
**	4
**	4
**	~	array
*/

void	write_4bytes(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

void	generate_header(const int *fd, unsigned char header[54], \
		int size, t_game *game)
{
	ft_memset(header, 0, 54);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	write_4bytes(header + 2, size);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	write_4bytes(header + 18, game->info.w);
	write_4bytes(header + 22, game->info.h);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
	write(*fd, header, 54);
}

void	generate_data(const int *fd, t_game *game)
{
	int					x;
	int					y;
	int					pad;
	const unsigned char	padding[3] = {0, 0, 0};

	y = game->info.h;
	pad = (4 - (game->info.w * 3) % 4) % 4;
	while (y >= 0)
	{
		x = 0;
		while (x < game->info.w)
		{
			write(*fd, &(game->buf[y][x]), 3);
			if (pad > 0)
				write(*fd, &padding, pad);
			x++;
		}
		y--;
	}
}

void	process_screenshot(int argc, char **argv, t_game *game)
{
	int				fd;
	int				size;
	unsigned char	header[54];

	if (argc != 3 || ft_strncmp("--save", argv[2], 6) != 0)
		return ;
	raycasting(game);
	size = 54 + ((3 * game->info.w) * game->info.h);
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT |\
						O_TRUNC | O_APPEND, 00755)) < 0)
		return ;
	generate_header(&fd, header, size, game);
	generate_data(&fd, game);
	ft_exit(0);
}
