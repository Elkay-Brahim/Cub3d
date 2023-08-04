/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_destance_x.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:43:13 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:43:30 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calcul_destance_x(t_beta *beta, int __j)
{
	int	c;

	if ((beta->__angle_start * 180) / PI > 90
		&& (beta->__angle_start * 180) / PI < 270)
	{
		c = (int)((beta->pos_px / B) + __j);
		beta->dx = beta->pos_px - c * B;
		beta->new_des_x = (beta->dx / cos(beta->__angle_start)) + 0.001;
	}
	else
	{
		c = (int)((beta->pos_px / B) + 1 - __j);
		beta->dx = beta->pos_px - c * B;
		beta->new_des_x = (beta->dx / cos(beta->__angle_start)) + 0.001;
	}
}
