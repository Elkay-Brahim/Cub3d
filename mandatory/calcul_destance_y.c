/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_destance_y.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:42:25 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:42:40 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calcul_destance_y(t_beta *beta, int __j)
{
	int	c;

	if (((beta->__angle_start * 180) / PI) > 180
		&& ((beta->__angle_start * 180) / PI) < 360)
	{
		c = (int)((beta->pos_py / B) + __j);
		beta->dy = beta->pos_py - c * B;
		beta->new_des_y = (beta->dy / sin(beta->__angle_start)) + 0.001;
	}
	else
	{
		c = (int)((beta->pos_py / B) + 1 - __j);
		beta->dy = beta->pos_py - c * B;
		beta->new_des_y = (beta->dy / sin(beta->__angle_start)) + 0.001;
	}
}
