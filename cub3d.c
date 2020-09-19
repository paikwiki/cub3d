/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:12:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/19 20:26:52 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int		key_press(int keycode)
{
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int		main(int argc, char *argv[])
{
	t_note	note;
	t_list	*lines;
	char	**map;
	void 	*mlx;
	void 	*win;

	if (argc < 2)
		exit_puterr("Map does not exist.\n");
	init_note(&note);
	lines = NULL;
	get_map_file(argv[1], &note, &lines);
	if (note.is_map == FALSE)
		exit_puterr("Fail to get information of map_size.");
	map = (char **)malloc(sizeof(char *) * note.map_height + 1);
	map[note.map_height] = 0;
	init_map(map, &note);
	set_map(map, &lines);
	free(lines);
	check_map_horizon(map, &note);
	check_map_vertical(map, &note);

	mlx = mlx_init();
	win = mlx_new_window(mlx, note.info_r[0], note.info_r[1], "cub3D");
	mlx_hook(win, X_EVENT_KEY_PRESS, 0, &key_press, &note);
	mlx_loop(mlx);
	return (0);
}
