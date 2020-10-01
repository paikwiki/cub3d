/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:41:10 by paikwiki          #+#    #+#             */
/*   Updated: 2020/10/01 21:41:10 by paikwiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	process_map(t_game *game, t_note *note, t_list **lines)
{
	init_map(game, note);
	set_map(game->map, note, lines);
	check_map(game->map, note);
}
