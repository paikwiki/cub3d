/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:12:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/24 14:07:52 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int		main_loop(t_mlx *mlx)
{
	draw_floor_ceiling(mlx);
	raycasting(mlx);
	return (0);
}

int		main(int argc, char **argv)
{
	t_mlx	*mlx;
	t_note	note;
	t_list	*lines;

	if (argc < 2)
		exit_puterr("Map does not exist.\n");
	init_note(&note);
	lines = NULL;
	get_map_file(argv[1], &note, &lines);
	if (note.is_map == FALSE)
		exit_puterr("Fail to get information of map_size.");
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	process_map(mlx, &note, &lines);
	free(lines);
	init_mlx(mlx, &note);
	mlx_hook(mlx->win, X_EVENT_KEY_EXIT, 0, &ft_exit, mlx);
	mlx_hook(mlx->win, X_EVENT_KEY_PRESS, 0, &key_press, mlx);
	mlx_loop_hook(mlx->ptr, &main_loop, mlx);
	mlx_loop(mlx->ptr);
	return (0);
}
