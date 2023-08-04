/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_of_y.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:38:20 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:38:34 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	break_of_y(t_beta *beta)
{
	beta->i = ((int)(beta->player_x * B
				+ beta->shift_x - beta->_pdx * beta->new_des_y) / B);
	beta->y = ((int)(beta->player_y * B
				+ beta->shift_y - beta->_pdy * beta->new_des_y) / B);
	if (beta->y <= 0 || beta->y > beta->map->height - 1
		|| beta->i <= 0 || beta->i > beta->map->width - 1)
		return (-1);
	if (beta->map->map[beta->y][beta->i] == 1
		|| beta->map->map[beta->y][beta->i] == 3)
	{
		if (beta->map->map[beta->y][beta->i] == 3 && beta->door == true)
		{
			beta->new_des_y = beta->new_des_y;
			beta->door_check = 1;
			return (-1);
		}
		if (beta->map->map[beta->y][beta->i] == 1)
			return (-1);
	}
	if (ray_effect_y(beta, (beta->__angle_start * 180) / PI, NULL) == -1)
		return (-1);
	return (1);
}
