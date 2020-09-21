/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:12:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/21 15:36:33 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int		key_press(int keycode)
{
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

void	process_map(char **map, t_note *note, t_list **lines)
{
	init_map(map, note);
	set_map(map, note, lines);
	check_map_horizon(map, note);
	check_map_vertical(map, note);
}

void	main_loop(t_note *note)
{
	t_mlx	mlx;
	void 	*img;
	int		img_width;
	int 	img_height;

	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, note->info_r[0], note->info_r[1], "cub3D");
	img = mlx_xpm_file_to_image(mlx.ptr, "../textures/fan.xpm", &img_width, &img_height);
	mlx_put_image_to_window(mlx.ptr, mlx.win, img, 50, 50);
	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 0, &key_press, &note);
	mlx_hook(mlx.win, X_EVENT_KEY_EXIT, 0, &close, &note);
	mlx_loop(mlx.ptr);
}

int		main(int argc, char **argv)
{
	t_note	note;
	t_list	*lines;
	char	**map;

	if (argc < 2)
		exit_puterr("Map does not exist.\n");
	init_note(&note);
	lines = NULL;
	get_map_file(argv[1], &note, &lines);
	if (note.is_map == FALSE)
		exit_puterr("Fail to get information of map_size.");
	map = (char **)malloc(sizeof(char *) * note.map_height + 1);
	map[note.map_height] = 0;
	process_map(map, &note, &lines);
	free(lines);
	main_loop(&note);
	return (0);
}
