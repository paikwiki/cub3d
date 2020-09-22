/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 22:57:52 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/22 10:22:34 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

# define FALSE 0
# define TRUE 1

# define HEX_UPPER "0123456789ABCDEF"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

# define KEY_ESC 53

typedef struct 	s_img
{
	void 	*ptr;
	int 	*data;
	int 	size_line;
	int 	bpp;
	int 	endian;
}				t_img;

typedef struct	s_mlx
{
	void 	*ptr;
	void 	*win;
}				t_mlx;

typedef struct	s_note
{
	int		c_rd;
	int		is_map;
	int		is_done;
	int		info_r[2];
	int 	rgb_ceiling;
	int 	rgb_floor;
	char	*info_no;
	char	*info_so;
	char	*info_we;
	char	*info_ea;
	char	*info_s;
	int 	player_xy[2];
	char 	player_dir;
	int		map_width;
	int		map_height;
}				t_note;

/*
** ============================================================================
**   utils.c
** ============================================================================
*/

int				count_info(t_note *note);
void			check_isdigit_all(char *str);
void			exit_puterr(const char *msg);
void			init_note(t_note *note);
void			ft_putstr(char *str);

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

void			check_rgb_range(int value);
int				get_int_from_hexstr(char *rgb_hex);
void			proc_parse_hexstr_from_int(char *rgb_hex, char *temp, int idx);
char			*parse_hexstr_from_int(int *dest);
void			get_rgb_int(int *dest, char **raw_values);
void			get_info_ceil_floor(char *line, t_note *note);

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

void			init_map(char **map, t_note *note);
char			check_valid_map_char(char chr);
void			set_map(char **map, t_note *note, t_list **lines);
void			get_map_file(char *file_path, t_note *note, t_list **lines);

/*
** ============================================================================
**   utils_player.c
** ============================================================================
*/

int				is_player_pos(char chr);
void			get_info_player_pos(t_note *note, char **map, int x, int y);

/*
** ============================================================================
**   temp_utils.c
** ============================================================================
*/

void			put_map(char **map, t_note *note);
#endif
