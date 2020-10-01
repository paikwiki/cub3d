/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 22:57:52 by paikwiki          #+#    #+#             */
/*   Updated: 2020/10/02 02:59:33 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>
# include <errno.h>
# include "cub3d_keys.h"
# include "cub3d_structs.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

# include <stdio.h>

# define FALSE 0
# define TRUE 1

# define HEX_UPPER "0123456789ABCDEF"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

# define TEX_WIDTH 64
# define TEX_HEIGHT 64

/*
** ============================================================================
**   functions which has same name between file and function
** ============================================================================
*/

void	calc_sprite(t_game *game);
void	check_map(char **map, t_note *note);
void	get_info_ceil_floor(char *line, t_note *note);
int		handle_key(int keycode, t_game *game);
void	init_game(t_game *game, t_note *note);
void	process_map(t_game *game, t_note *note, t_list **lines);
void	process_screenshot(int argc, char **argv, t_game *game);
void	raycasting(t_game *game);
void	read_cub_file(char *file_path, t_note *note, t_list **lines);
void	set_map(char **map, t_note *note, t_list **lines);
void	set_info(char *line, t_note *note);

/*
** ============================================================================
**   utils.c
** ============================================================================
*/

void	init_note(t_note *note);
void	check_isdigit_all(char *str);
void	ft_exit_puterr(const char *msg);
void	ft_putstr(char *str);
int		ft_exit(int exit_val);

/*
** ============================================================================
**   utils_info.c
** ============================================================================
*/

int		count_info(t_note *note);
int		char_to_hexadecimal(char chr);
void	check_rgb_range(int value);

/*
** ============================================================================
**   utils_texture.c
** ============================================================================
*/

void	init_texture_buffer(t_game *game);
void	init_texture(t_game *game);

/*
** ============================================================================
**   utils_map.c
** ============================================================================
*/

int		is_player_pos(char chr);
int		is_sprite_pos(char chr);
int		get_wall_char(char **map, int x_start, int y_start);
void	init_map(t_game *game, t_note *note);

/*
** ============================================================================
**   get_sprite.c
** ============================================================================
*/

void	sort_sprite_by_dist(t_game *game);
void	get_sprite(t_game *game);

/*
** ============================================================================
**   utils_raycasting.c
** ============================================================================
*/

void	calc_wall(t_game *game, t_raycast_note *rc, int idx);
void	set_raycast_note(t_raycast_note *rc, t_game *game, int idx);
#endif
