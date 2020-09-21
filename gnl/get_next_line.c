/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:11:48 by cbaek             #+#    #+#             */
/*   Updated: 2020/09/18 21:23:49 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*ft_get_nlc_addr(char *s)
{
	size_t	idx;

	if (s == 0)
		return (NULL);
	idx = 0;
	while (s[idx] != '\0')
	{
		if (s[idx] == '\n')
			return (&s[idx]);
		idx++;
	}
	return (0);
}

static int	handle_line(char **line, char **note, char *nlc_addr)
{
	char *temp;

	if (nlc_addr != NULL)
	{
		*line = ft_strndup(*note, nlc_addr - *note);
		temp = ft_strndup(nlc_addr + 1, ft_strlen(nlc_addr + 1));
		free(*note);
		*note = temp;
		return (GNL_NL);
	}
	if (*note != NULL)
	{
		*line = *note;
		*note = NULL;
	}
	else
		*line = ft_strndup("", 1);
	return (GNL_EOF);
}

int			get_next_line(const int fd, char **line)
{
	static char	*note[OPEN_MAX];
	char		buff[BUFFER_SIZE + 1];
	char		*temp;
	int			rd_byte;
	char		*nlc_addr;

	if ((fd < 0 || line == NULL) != 0)
		return (GNL_ERROR);
	while ((nlc_addr = ft_get_nlc_addr(note[fd])) == 0
			&& ((rd_byte = read(fd, buff, BUFFER_SIZE)) > 0))
	{
		buff[rd_byte] = '\0';
		temp = note[fd] == NULL ? ft_strndup(buff, rd_byte) :
				ft_strjoin(note[fd], buff);
		if (note[fd] != NULL)
			free(note[fd]);
		note[fd] = temp;
	}
	if (rd_byte < 0)
		return (GNL_ERROR);
	return (handle_line(line, &note[fd], nlc_addr));
}
