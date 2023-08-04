/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_beta.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:16:58 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:48:28 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_beta(t_beta *beta, t_map_s *first)
{
	beta->_const = first->direction * 0.0174532925;
	beta->player_x = first->player_x;
	beta->player_y = first->player_y;
	beta->f_color = first->f_color;
	beta->c_color = first->c_color;
	beta->door = true;
	beta->pdx = cos(beta->_const);
	beta->pdy = sin(beta->_const);
	beta->i = 0;
	beta->y = 0;
	beta->shift_x = 0;
	beta->shift_y = 0;
	ft_textur(beta, first);
	beta->map = ft_calloc(sizeof(t_map), 1);
	beta->map->map = first->map;
	beta->map->width = first->width ;
	beta->map->height = first->height;
	beta->first = first;
}
