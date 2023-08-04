/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_raycasting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:37:23 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:37:49 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_env_raycasting(t_beta *beta)
{
	beta->wall_x = 0;
	beta->_angle = beta->_const;
	beta->__angle_start = beta->_const - 0.523598776;
	beta->__angle_end = beta->_const + 0.523598776;
	beta->pos_px = (beta->player_x * B + beta->shift_x);
	beta->pos_py = (beta->player_y * B + beta->shift_y);
	if (beta->_const - 0.523598776 <= 0)
	{
		beta->__angle_start = beta->_const + 5.75958653;
		beta->__angle_end = beta->_const + 6.28318531 + 0.523598776;
	}
	return ;
}
