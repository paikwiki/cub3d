/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:12:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/24 12:03:56 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"
#include <stdio.h>
void	process_map(t_mlx *mlx, t_note *note, t_list **lines)
{
	init_map(mlx, note);
	set_map(mlx->map, note, lines);
	check_map_horizon(mlx->map, note);
	check_map_vertical(mlx->map, note);
}

void    init_param(t_mlx *mlx, double px, double py)
{
	mlx->prm.px = px + 0.5;
	mlx->prm.py = py + 0.5;
	mlx->prm.dx = 0;
	mlx->prm.dy = -1;
	mlx->prm.m_spd = 0.1;
	mlx->prm.r_spd = 0.1;
	mlx->prm.pln_x = 0.66;
	mlx->prm.pln_y = 0;
}

/*
** counterclockwise direction: -1;
** clockwise direction: 1;
*/

void	rotate_player(t_mlx *mlx, int dir)
{
	double	dx_old;
	double	pln_x_old;

	dx_old = mlx->prm.dx;
	mlx->prm.dx = mlx->prm.dx * cos(dir * mlx->prm.r_spd) - mlx->prm.dy * sin(dir * mlx->prm.r_spd);
	mlx->prm.dy = dx_old * sin(dir * mlx->prm.r_spd) + mlx->prm.dy * cos(dir * mlx->prm.r_spd);
	pln_x_old = mlx->prm.pln_x;
	mlx->prm.pln_x = mlx->prm.pln_x * cos(dir * mlx->prm.r_spd) - mlx->prm.pln_y * sin(dir * mlx->prm.r_spd);
	mlx->prm.pln_y = pln_x_old * sin(dir * mlx->prm.r_spd) + mlx->prm.pln_y * cos(dir * mlx->prm.r_spd);
}


int     key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W)
	{
		if (mlx->map[(int)(mlx->prm.py)][(int)(mlx->prm.px + mlx->prm.dx * mlx->prm.m_spd)] != '1')
			mlx->prm.px += mlx->prm.dx * mlx->prm.m_spd;
		if (mlx->map[(int)(mlx->prm.py + mlx->prm.dy * mlx->prm.m_spd)][(int)(mlx->prm.px)] != '1')
			mlx->prm.py += mlx->prm.dy * mlx->prm.m_spd;
	}
	if (keycode == KEY_S)
	{
		if (mlx->map[(int)(mlx->prm.py)][(int)(mlx->prm.px - mlx->prm.dx * mlx->prm.m_spd)] != '1')
			mlx->prm.px -= mlx->prm.dx * mlx->prm.m_spd;
		if (mlx->map[(int)(mlx->prm.py - mlx->prm.dy * mlx->prm.m_spd)][(int)(mlx->prm.px)] != '1')
			mlx->prm.py -= mlx->prm.dy * mlx->prm.m_spd;
	}
	if (keycode == KEY_A)
	{
		if (mlx->map[(int)(mlx->prm.py)][(int)(mlx->prm.px - mlx->prm.pln_x * mlx->prm.m_spd)] != '1')
			mlx->prm.px -= mlx->prm.pln_x * mlx->prm.m_spd;
		if (mlx->map[(int)(mlx->prm.py - mlx->prm.pln_y * mlx->prm.m_spd)][(int)(mlx->prm.px)] != '1')
			mlx->prm.py -= mlx->prm.pln_y * mlx->prm.m_spd;
	}
	if (keycode == KEY_D)
	{
		if (mlx->map[(int)(mlx->prm.py)][(int)(mlx->prm.px + mlx->prm.pln_x * mlx->prm.m_spd)] != '1')
			mlx->prm.px += mlx->prm.pln_x * mlx->prm.m_spd;
		if (mlx->map[(int)(mlx->prm.py + mlx->prm.pln_y * mlx->prm.m_spd)][(int)(mlx->prm.px)] != '1')
			mlx->prm.py += mlx->prm.pln_y * mlx->prm.m_spd;
	}
	if (keycode == KEY_RA)
		rotate_player(mlx, 1);
	if (keycode == KEY_LA)
		rotate_player(mlx, -1);
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

void	verLine(t_mlx *mlx, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(mlx->ptr, mlx->win, x, y, color);
		y++;
	}
}

void	set_raycast_note(t_raycast_note *rc, t_mlx *mlx, int idx)
{
	rc->cam_x = 2 * idx / (double)mlx->info.w - 1;
	rc->rd_x = mlx->prm.dx + mlx->prm.pln_x * rc->cam_x;
	rc->rd_y = mlx->prm.dy + mlx->prm.pln_y * rc->cam_x;
	rc->mx = (int)mlx->prm.px;
	rc->my = (int)mlx->prm.py;
	rc->side_dx = 0;
	rc->side_dy = 0;
	rc->delta_dx = fabs(1 / rc->rd_x);
	rc->delta_dy = fabs(1 / rc->rd_y);
	rc->pp_walld = 0;
	rc->st_x = 0;
	rc->st_y = 0;
	rc->hit = 0;
	rc->side = 0;
	rc->color = 0x0000FF;
	rc->lineHeight = 0;
	rc->drawStart = 0;
	rc->drawEnd = 0;
}

void	raycasting(t_mlx *mlx)
{
	t_raycast_note	rc;
	int				idx;

	idx = 0;
	while (idx < mlx->info.w)
	{
		set_raycast_note(&rc, mlx, idx);
		if (rc.rd_x < 0)
		{
			rc.st_x = -1;
			rc.side_dx = (mlx->prm.px - rc.mx) * rc.delta_dx;
		}
		else
		{
			rc.st_x = 1;
			rc.side_dx = (rc.mx + 1.0 - mlx->prm.px) * rc.delta_dx;
		}
		if (rc.rd_y < 0)
		{
			rc.st_y = -1;
			rc.side_dy = (mlx->prm.py - rc.my) * rc.delta_dy;
		}
		else
		{
			rc.st_y = 1;
			rc.side_dy = (rc.my + 1.0 - mlx->prm.py) * rc.delta_dy;
		}
		while (rc.hit == 0)
		{
			if (rc.side_dx < rc.side_dy)
			{
				rc.side_dx += rc.delta_dx;
				rc.mx += rc.st_x;
				rc.side = 0;
			}
			else
			{
				rc.side_dy += rc.delta_dy;
				rc.my += rc.st_y;
				rc.side = 1;
			}
			if (mlx->map[rc.my][rc.mx] > '0')
				rc.hit = 1;
		}
		if (rc.side == 0)
			rc.pp_walld = (rc.mx - mlx->prm.px + (1 - rc.st_x) / 2) / rc.rd_x;
		else
			rc.pp_walld = (rc.my - mlx->prm.py + (1 - rc.st_y) / 2) / rc.rd_y;
		rc.lineHeight = (int)(mlx->info.h / rc.pp_walld);
		rc.drawStart = -rc.lineHeight / 2 + mlx->info.h / 2;
		rc.drawEnd = rc.lineHeight / 2 + mlx->info.h / 2;
		if(rc.drawStart < 0)
			rc.drawStart = 0;
		if (rc.drawEnd >= mlx->info.h)
			rc.drawEnd = mlx->info.h - 1;
		if (rc.side == 1)
			rc.color = rc.color / 2;
		verLine(mlx, idx, rc.drawStart, rc.drawEnd, rc.color);
//		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
		idx++;
	}
}

void	draw_floor_ceiling(t_mlx *mlx)
{
	int		cnt_w;
	int 	cnt_h;

	cnt_h = -1;
	while (++cnt_h < (mlx->info.h / 2) && (cnt_w = -1) == -1)
		while (++cnt_w < mlx->info.w)
			mlx->img.data[cnt_h * mlx->info.w + cnt_w] = mlx->info.color_c;
	cnt_h = (mlx->info.h / 2) - 1;
	while (++cnt_h < mlx->info.h && (cnt_w = -1) == -1)
		while (++cnt_w < mlx->info.w)
			mlx->img.data[cnt_h * mlx->info.w + cnt_w] = mlx->info.color_f;
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
}

int		main_loop(t_mlx *mlx)
{
	draw_floor_ceiling(mlx);
	raycasting(mlx);
	return (0);
}

int		ft_exit(int exit_val)
{
	exit(exit_val);
	return (exit_val);
}

void 	init_mlx(t_mlx *mlx, t_note *note)
{
	init_param(mlx, note->player_xy[0], note->player_xy[1]);
	mlx->info.w = note->info_r[0];
	mlx->info.h = note->info_r[1];
	mlx->info.color_f = note->rgb_floor;
	mlx->info.color_c = note->rgb_ceiling;
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, mlx->info.w,
							  mlx->info.h, "cub3D");
	mlx->img.ptr = mlx_new_image(mlx->ptr, mlx->info.w, mlx->info.h);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr,
			&mlx->img.bpp, &mlx->img.size_line, &mlx->img.endian);
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
