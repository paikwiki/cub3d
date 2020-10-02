/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structues.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 18:36:27 by paikwiki          #+#    #+#             */
/*   Updated: 2020/10/02 20:10:13 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include "../libft/libft.h"

typedef struct	s_sprite
{
	double	x;
	double	y;
	double	distance;
}				t_sprite;

typedef struct	s_img
{
	void	*img_ptr;
	int		*data;
	int		size_line;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
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
	int			w;
	int			h;
	int			color_c;
	int			color_f;
	int			cnt_sprite;
	t_sprite	**sprites;
	double		*z_buffer;
	char		*tex_no;
	char		*tex_so;
	char		*tex_we;
	char		*tex_ea;
	char		*tex_s;
}				t_info;

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		**buf;
	int		**texture;
	t_img	img;
	t_info	info;
	t_param	prm;
}				t_game;

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
	t_list	*sprites;
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
	int		line_height;
	int		draw_start;
	int		draw_end;
}				t_raycast_note;

typedef struct	s_sprite_note
{
	double	spr_x;
	double	spr_y;
	double	inv_det;
	double	trns_x;
	double	trns_y;
	int		sprite_screen_x;
	int		sprite_h;
	int		sprite_w;
	int		draw_start_x;
	int		draw_end_x;
	int		draw_start_y;
	int		draw_end_y;
	int		tex_x;
	int		tex_y;
	int		d;
	int		color;
}				t_sprite_note;

#endif
