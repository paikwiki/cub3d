/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 22:57:52 by paikwiki          #+#    #+#             */
/*   Updated: 2020/09/15 18:48:00 by paikwiki         ###   ########.fr       */
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

# define TRUE 1
# define FALSE 0
# define MAP_VAL_CHARS " 012NWES"

typedef struct	s_note
{
	int		c_rd;
	int 	is_map;
	int 	is_done;
	char 	*info_r;
	char 	*info_no;
	char 	*info_so;
	char 	*info_we;
	char 	*info_ea;
	char 	*info_s;
	char 	*info_f;
	char 	*info_c;
	int 	c_info;
	int 	c_temp;
}				t_note;
#endif
