/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 22:57:52 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/16 15:58:34 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include "./lib/gnl/get_next_line.h"
# include "./lib/libft/libft.h"

# define FALSE 0
# define TRUE 1

# define NO 0
typedef struct	s_note
{
	int		c_rd;
	int 	is_map;
	int 	is_done;
	int 	info_r[2];
	int 	info_f[3];
	int 	info_c[3];
	char 	*info_no;
	char 	*info_so;
	char 	*info_we;
	char 	*info_ea;
	char 	*info_s;
	int 	map[2];

}				t_note;
#endif
