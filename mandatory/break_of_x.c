/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_of_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:40:15 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 19:16:33 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	break_of_x(t_beta *beta)
{
	beta->i = ((int)(beta->player_x * B
				+ beta->shift_x - beta->_pdx * beta->new_des_x) / B);
	beta->y = ((int)(beta->player_y * B
				+ beta->shift_y - beta->_pdy * beta->new_des_x) / B);
	if (beta->y <= 0 || beta->y > beta->map->height - 1
		|| beta->i <= 0 || beta->i > beta->map->width - 1)
		return (-1);
	if (beta->map->map[beta->y][beta->i] == 1)
	{
		return (-1);
	}
	if (ray_effect_x(beta, (beta->__angle_start * 180) / PI, NULL) == -1)
		return (-1);
	return (1);
}
