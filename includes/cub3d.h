/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 22:57:52 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/27 01:50:26 by paikwiki         ###   ########.fr       */
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
**   utils.c
** ============================================================================
*/

void			init_note(t_note *note);
void			check_isdigit_all(char *str);
void			ft_exit_puterr(const char *msg);
void			ft_putstr(char *str);
int				ft_exit(int exit_val);

/*
** ============================================================================
**   utils_info.c
** ============================================================================
*/

int				count_info(t_note *note);
int				char_to_hexadecimal(char chr);
void			check_rgb_range(int value);

/*
** ============================================================================
**   utils_inits.c
** ============================================================================
*/

void			init_mlx(t_mlx *mlx, t_note *note);
void			init_map(t_mlx *mlx, t_note *note);

/*
** ============================================================================
**   utils_map.c
** ============================================================================
*/

int				get_wall_char(char **map, int x_start, int y_start);
char			check_valid_map_char(char chr);
void			set_map(char **map, t_note *note, t_list **lines);
void			process_map(t_mlx *mlx, t_note *note, t_list **lines);
void			read_cub_file(char *file_path, t_note *note, t_list **lines);

/*
** ============================================================================
**   calc_sprite.c
** ============================================================================
*/

void		 	sort_sprite_by_dist(t_mlx *mlx);
void 			calc_sprite(t_mlx *mlx);

/*
** ============================================================================
**   utils_sprite.c
** ============================================================================
*/

void			generate_info_sprite_pos(t_note *note, char **map, int x, int y);

/*
** ============================================================================
**   utils_player.c
** ============================================================================
*/

void			set_player_dir(t_mlx *mlx, t_note *note);
int				is_player_pos(char chr);
void			generate_info_p_pos(t_note *note, char **map, int x, int y);

/*
** ============================================================================
**   utils_raycasting.c
** ============================================================================
*/

void			calc_wall(t_mlx *mlx, t_raycast_note *rc, int idx);
void			set_raycast_note(t_raycast_note *rc, t_mlx *mlx, int idx);

/*
** ============================================================================
**   raycasting.c
** ============================================================================
*/

void			raycasting(t_mlx *mlx);

/*
** ============================================================================
**   generate_info.c
** ============================================================================
*/

void			generate_info(char *line, t_note *note);

/*
** ============================================================================
**   get_info_ceil_floor.c
** ============================================================================
*/

void			get_info_ceil_floor(char *line, t_note *note);

/*
** ============================================================================
**   check_map.c
** ============================================================================
*/

void			check_map(char **map, t_note *note);

/*
** ============================================================================
**   handle_key.c
** ============================================================================
*/

int				handle_key(int keycode, t_mlx *mlx);

/*
** ============================================================================
**   temp_utils.c
** ============================================================================
*/

void			ver_line(t_mlx *mlx, int x, int y1, int y2, int color);
void			put_map(char **map);
#endif
