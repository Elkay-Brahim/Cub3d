/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dda.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:44:38 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:44:50 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	_dda(t_beta *beta)
{
	t_dda	*dda;

	dda = ft_calloc(1, sizeof(t_dda));
	dda->start_x = beta->pos_px;
	dda->start_y = beta->pos_py;
	dda->end_x = beta->player_x * B + beta->shift_x + beta->_pdx * beta->__des;
	dda->end_y = beta->player_y * B + beta->shift_y + beta->_pdy * beta->__des;
	dda->m_x = 0;
	dda->m_y = 0;
	dda->color = 0xE50000;
	dda->dx = ((dda->start_x + dda->m_x) - dda->end_x);
	dda->dy = ((dda->start_y + dda->m_y) - dda->end_y);
	dda->max = fmax(fabs(dda->dx), fabs(dda->dy));
	dda->dx = dda->dx / dda->max;
	dda->dy = dda->dy / dda->max;
	while (dda->max-- > 0)
	{
		my_mlx_pixel_put(&beta->image, dda->start_x, dda->start_y, dda->color);
		dda->start_x += dda->dx;
		dda->start_y += dda->dy;
	}
	free(dda);
}
