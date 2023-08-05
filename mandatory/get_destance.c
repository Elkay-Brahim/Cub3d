/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_destance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:41:33 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/05 10:32:59 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_destance(t_beta *beta, float angle)
{
	if (fabs(beta->new_des_x) < fabs(beta->new_des_y))
	{
		beta->__des = fabs(beta->new_des_x);
		(beta->__des < 1) && (beta->__des = 1);
		beta->inter_wall_side = WALL_SIDE_X;
		if (angle > 90 && angle < 270)
			beta->textur_i = TEXTUR_E;
		else
			beta->textur_i = TEXTUR_W;
	}
	else
	{
		beta->__des = fabs(beta->new_des_y);
		beta->inter_wall_side = WALL_SIDE_Y;
		if ((angle > 0 && angle < 180) || angle > 360)
			beta->textur_i = TEXTUR_N;
		else
			beta->textur_i = TEXTUR_S;
	}
	beta->intersect_x = ((beta->pos_px - beta->_pdx * beta->__des));
	beta->intersect_y = ((beta->pos_py - beta->_pdy * beta->__des));
}
