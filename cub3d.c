/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:12:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/14 15:50:27 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_putstr(char *str)
{
	int idx;

	if (!str)
		return ;
	idx = 0;
	while (str[idx] != 0)
		write(1, &str[idx++], 1);
	return ;
}

void	exit_puterr(const char *msg)
{
	ft_putstr((char *)"Error:\n");
	ft_putstr((char *)msg);
	exit(EXIT_FAILURE);
}

int		main(int argc, char *argv[])
{
	char	*line;
	int		fd;
	int		rd_byte;

	if (argc < 2)
	{
		exit_puterr("Map does not exist.\n");
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) > 0)
	{
		while ((rd_byte = get_next_line(fd, &line)) > 0)
			printf("%s\n", line);
		if (*line)
			exit_puterr("No newline after map.");
		free(line);
	}
	else
		exit_puterr("Fail to open a map file.");
	return (0);
}
