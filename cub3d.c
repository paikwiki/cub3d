/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:12:02 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/16 11:22:00 by paikwiki         ###   ########.fr       */
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
	note->c_info = 0;
}

void	init_lst_line(t_list *lst_line)
{
	lst_line->content = 0;
	lst_line->next = 0;
}

int		is_info_line(char *key, char *line, t_note *note)
{
	if (note->c_info < 8)
	{
		note->c_info += 1;
		return (TRUE);
	}
	return (FALSE);
}

char *get_info_key(char *line)
{
	size_t	len;
	size_t	len_val;
	char	chr_2nd;

	char	*key;
	len = ft_strlen(line);
	len_val = 0;
	if (len > 2 && (ft_strchr(INFO_VALID_FIRST_CHAR, line[0])) > 0 && (chr_2nd = (ft_strchr(INFO_VALID_SECOND_CHAR, line[1])[0])) > 0)
	{
		if (chr_2nd == ' ')
		{
			printf("Get info: %c\n", line[0]);
		}
		else
		{
			printf("Get info: %c%c\n", line[0], line[1]);
		}
	}
	key = (char *)malloc(sizeof(char) * len_val + 1);

	return (0);
}

int 	collect_info(char *line, char *note)
{
	if (is_info_line(get_info_key(line), line, note) == TRUE)
		return (FALSE);
	return (TRUE);
}

void 	check_line(char *line, t_note *note)
{
	note->is_map = collect_info(line, note);
//	printf("%s\n", line);
	return ;
}

int		main(int argc, char *argv[])
{
	char	*line;
	int		fd;
	t_note	note;
	t_list  *lst_line;

	if (argc < 2)
	{
		exit_puterr("Map does not exist.\n");
		return (0);
	}

	init_note(&note);
	init_lst_line(&lst_line);
	if ((fd = open(argv[1], O_RDONLY)) > 0)
	{
		note.is_done = FALSE;
		while (note.is_done == FALSE)
		{
			if ((note.c_rd = get_next_line(fd, &line)) <= 0)
				note.is_done = TRUE;
			check_line(line, &note);
			if (note.is_map == TRUE)
			{
				if (note.c_info >= 8 && ft_lstsize(lst_line) < 1)
					lst_line = ft_lstnew(line);
				else
					ft_lstadd_back(&lst_line, ft_lstnew(line));
				printf("%s\n", line);
				free(line);
			}
		}
		printf("size: %d\n", ft_lstsize(lst_line));
	}
	else
		exit_puterr("Fail to open a map file.");
	return (0);
}
