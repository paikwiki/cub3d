/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:12:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/16 19:21:57 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_putstr(char *str)
{
	int idx;

	if (!str)
		return ;
	idx = 0;
	while (str[idx] != 0)
		write(1, &str[idx++], 1);
	return ;
}

void	exit_puterr(const char *msg)
{
	ft_putstr((char *)"Error:\n");
	ft_putstr((char *)msg);
	exit(EXIT_FAILURE);
}

void 	init_note(t_note *note)
{
	note->c_rd = 0;
	note->is_map = 0;
	note->is_done = 0;
	note->info_r[0] = -1;
	note->info_r[1] = -1;
	note->info_no = 0;
	note->info_so = 0;
	note->info_we = 0;
	note->info_ea = 0;
	note->info_s = 0;
	note->info_f[0] = -1;
	note->info_f[1] = -1;
	note->info_f[2] = -1;
	note->info_c[0] = -1;
	note->info_c[1] = -1;
	note->info_c[2] = -1;
	note->map[0] = 0;
	note->map[1] = 0;
}

int 	count_info(t_note *note)
{
	int	cnt;

	cnt = 0;
	if (note->info_r[0] != -1)
		cnt++;
	if (note->info_no != 0)
		cnt++;
	if (note->info_so != 0)
		cnt++;
	if (note->info_we != 0)
		cnt++;
	if (note->info_ea != 0)
		cnt++;
	if (note->info_s != 0)
		cnt++;
	if (note->info_f[0] != -1)
		cnt++;
	if (note->info_c[0] != -1)
		cnt++;
	return (cnt);
}

void 	get_info_texture(char *line, t_note *note)
{
	char	*value;

	value = ft_strndup((char *)&line[4], ft_strlen((const char *)&line[4]));

	if (ft_strncmp((const char *)line, "NO ", 3) == 0)
		note->info_no = value;
	else if (ft_strncmp((const char *)line, "SO ", 3) == 0)
		note->info_so = value;
	else if (ft_strncmp((const char *)line, "WE ", 3) == 0)
		note->info_we = value;
	else if (ft_strncmp((const char *)line, "EA ", 3) == 0)
		note->info_ea = value;
	else if (ft_strncmp((const char *)line, "S ", 2) == 0)
		note->info_s = value;
	return ;
}

void	get_info_ceil_floor(char *line, t_note *note)
{

	char	*raw_str;
	char	**raw_values;

	raw_str = ft_strndup((char *)&line[2], ft_strlen((const char *)&line[2]));
	raw_values = ft_split(raw_str, ',');
	if (ft_strncmp((const char *)line, "F ", 2) == 0)
	{
		note->info_f[0] = ft_atoi(raw_values[0]);
		note->info_f[1] = ft_atoi(raw_values[1]);
		note->info_f[2] = ft_atoi(raw_values[2]);
	}
	else if (ft_strncmp((const char *)line, "C ", 2) == 0)
	{
		note->info_c[0] = ft_atoi(raw_values[0]);
		note->info_c[1] = ft_atoi(raw_values[1]);
		note->info_c[2] = ft_atoi(raw_values[2]);
	}
	return ;
}

void 	get_info_resolution(char *line, t_note *note)
{
	char	*raw_str;
	char	**raw_values;

	raw_str = ft_strndup((char *)&line[2], ft_strlen((const char *)&line[2]));
	raw_values = ft_split(raw_str, ' ');
	note->info_r[0] = ft_atoi(raw_values[0]);
	note->info_r[1] = ft_atoi(raw_values[1]);
	return ;
}

void	generate_info(char *line, t_note *note)
{
	if (ft_strncmp((const char *)line, "R ", 2) == 0)
		get_info_resolution(line, note);
	else if (ft_strncmp((const char *)line, "F ", 2) == 0 ||
			ft_strncmp((const char *)line, "C ", 2) == 0)
		get_info_ceil_floor(line, note);
	else if (ft_strncmp((const char *)line, "NO ", 3) == 0 ||
			ft_strncmp((const char *)line, "SO ", 3) == 0 ||
			ft_strncmp((const char *)line, "WE ", 3) == 0 ||
			ft_strncmp((const char *)line, "EA ", 3) == 0 ||
			ft_strncmp((const char *)line, "S ", 2) == 0)
		get_info_texture(line, note);
	return ;
}

int 	collect_info(char *line, t_note *note)
{
	generate_info(line, note);
	if (count_info(note) < 8)
		return (FALSE);
	return (TRUE);
}

void 	check_line(char *line, t_note *note)
{
	note->is_map = collect_info(line, note);
	return ;
}

void	init_map(char **map, t_note *note)
{
	char	*line;
	int 	idx;
	int		idx_sub;

	idx = 0;
	while (idx <= note->map[1])
	{
		line = (char *)malloc((sizeof(char) * note->map[0]) + 1);
		line[note->map[0]] = '\0';

		idx_sub = 0;
		while (idx_sub < note->map[0])
		{
			line[idx_sub] = ' ';
			idx_sub++;
		}
		map[idx] = line;
		idx++;
	}
	return ;
}

void 	set_map(char **map, t_list **lst_line)
{
	int 	idx;
	int 	idx_map;
	t_list	*crr_item;
	char	*line;

	idx_map = 0;
	while(1)
	{
		crr_item = *lst_line;
		idx = 0;

		line = (char *)(crr_item->content);
		while(line[idx] != '\0')
		{
			map[idx_map][idx] = line[idx];
			idx++;
		}
		if ((*lst_line)->next != 0)
		{
			lst_line = &((*lst_line)->next);
		}
		else {
			return ;
		}
		idx_map++;
	}
}

int		main(int argc, char *argv[])
{
	char	*line;
	int		fd;
	t_note	note;
	t_list  *lst_line;
	char 	**map;

	if (argc < 2)
		exit_puterr("Map does not exist.\n");

	init_note(&note);
	lst_line = NULL;

	if ((fd = open(argv[1], O_RDONLY)) > 0)
	{
		note.is_done = FALSE;
		while (note.is_done == FALSE)
		{
			if ((note.c_rd = get_next_line(fd, &line)) <= 0)
				note.is_done = TRUE;
			if (note.is_map == TRUE)
			{
				note.map[0] = ft_strlen(line) > note.map[0] ? (int)ft_strlen(line) : note.map[0];
				if (!lst_line)
					lst_line = ft_lstnew(line);
				else
					ft_lstadd_back(&lst_line, ft_lstnew(line));
			}
			check_line(line, &note);
		}
		free(line);
		note.map[1] = ft_lstsize(lst_line);
	}
	else
		exit_puterr("Fail to open a map file.");
	map = (char **)malloc(sizeof(char *) * note.map[1] + 1);
	map[note.map[1]] = 0;
	init_map(map, &note);
	set_map(map, &lst_line);

	for (int i = 0; i < note.map[1]; i++)
		printf("$%s$\n", map[i]);
	return (0);
}
