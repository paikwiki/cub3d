/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:41:10 by cbaek             #+#    #+#             */
/*   Updated: 2020/10/02 23:14:40 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	process_map(t_game *game, t_note *note, t_list **lines)
{
	init_map(game, note);
	set_map(game->map, note, lines);
	check_map(game->map, note);
}
