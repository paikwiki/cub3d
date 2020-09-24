/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 22:57:52 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/24 18:37:21 by paikwiki         ###   ########.fr       */
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

# define FALSE 0
# define TRUE 1

# define HEX_UPPER "0123456789ABCDEF"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

/*
** ============================================================================
**   utils.c
** ============================================================================
*/

int				count_info(t_note *note);
void			check_isdigit_all(char *str);
void			exit_puterr(const char *msg);
void			ft_putstr(char *str);
int				ft_exit(int exit_val);

/*
** ============================================================================
**   utils_info.c
** ============================================================================
*/

void			get_info_texture(char *line, t_note *note, int idx);
void			get_info_resolution(char *line, t_note *note);
void			generate_info(char *line, t_note *note);

/*
** ============================================================================
**   utils_info2.c
** ============================================================================
*/

int				get_int_from_hexstr(char *rgb_hex);
void			proc_parse_hexstr_from_int(char *rgb_hex, char *temp, int idx);
char			*parse_hexstr_from_int(int *dest);
void			get_rgb_int(int *dest, char **raw_values);
void			get_info_ceil_floor(char *line, t_note *note);

/*
** ============================================================================
**   utils_info3.c
** ============================================================================
*/

int				atoi_hexchar(char chr);
void			check_rgb_range(int value);

/*
** ============================================================================
**   utils_map.c
** ============================================================================
*/

int				get_wall_char(char **map, int x_start, int y_start);
void			check_map_horizon(char **map, t_note *note);
void			check_map_vertical(char **map, t_note *note);
void			check_mapline_horizon(char **map, int xs, int xe, int y);
void			check_mapline_vertical(char **map, int ys, int ye, int x);

/*
** ============================================================================
**   utils_map2.c
** ============================================================================
*/

char			check_valid_map_char(char chr);
void			set_map(char **map, t_note *note, t_list **lines);
void			process_map(t_mlx *mlx, t_note *note, t_list **lines);
void			get_map_file(char *file_path, t_note *note, t_list **lines);

/*
** ============================================================================
**   utils_inits.c
** ============================================================================
*/

void			init_map(t_mlx *mlx, t_note *note);
void			init_mlx(t_mlx *mlx, t_note *note);
void			init_param(t_mlx *mlx, double px, double py);
void			init_note(t_note *note);

/*
** ============================================================================
**   utils_player.c
** ============================================================================
*/

int				is_player_pos(char chr);
void			get_info_player_pos(t_note *note, char **map, int x, int y);

/*
** ============================================================================
**   raycasting.c
** ============================================================================
*/

void			raycasting(t_mlx *mlx);
void			draw_floor_ceiling(t_mlx *mlx);

/*
** ============================================================================
**   handle_key_event.c
** ============================================================================
*/

int				key_press(int keycode, t_mlx *mlx);

/*
** ============================================================================
**   temp_utils.c
** ============================================================================
*/

void			ver_line(t_mlx *mlx, int x, int y1, int y2, int color);
void			put_map(char **map);
#endif
