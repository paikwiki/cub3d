/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 22:57:52 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/24 13:34:27 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>
# include <errno.h>
# include "keys.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

# define FALSE 0
# define TRUE 1

# define HEX_UPPER "0123456789ABCDEF"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

typedef struct	s_img
{
	void	*ptr;
	int		*data;
	int		size_line;
	int		bpp;
	int		endian;
}				t_img;

typedef struct	s_param
{
	double	px;
	double	py;
	double	dx;
	double	dy;
	double	m_spd;
	double	r_spd;
	double	pln_x;
	double	pln_y;
}				t_param;

typedef struct	s_info
{
	int		w;
	int		h;
	int		color_c;
	int		color_f;
}				t_info;

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
	char		**map;
	t_img		img;
	t_info		info;
	t_param		prm;
}				t_mlx;

typedef struct	s_note
{
	int		c_rd;
	int		is_map;
	int		is_done;
	int		info_r[2];
	int		rgb_ceiling;
	int		rgb_floor;
	char	*info_no;
	char	*info_so;
	char	*info_we;
	char	*info_ea;
	char	*info_s;
	int		player_xy[2];
	char	player_dir;
	int		map_width;
	int		map_height;
}				t_note;

typedef struct	s_raycast_note
{
	double	rd_x;
	double	rd_y;
	double	cam_x;
	int		mx;
	int		my;
	double	side_dx;
	double	side_dy;
	double	delta_dx;
	double	delta_dy;
	double	pp_walld;
	int		st_x;
	int		st_y;
	int		hit;
	int		side;
	int		color;
	int		line_height;
	int		draw_start;
	int		draw_end;
}				t_raycast_note;

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

void			init_map(t_mlx *mlx, t_note *note);
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
**   handle_key_event.c
** ============================================================================
*/

int				key_press(int keycode, t_mlx *mlx);
/*
** ============================================================================
**   temp_utils.c
** ============================================================================
*/

void			put_map(char **map);
#endif
