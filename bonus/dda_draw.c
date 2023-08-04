/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:31:47 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:31:58 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_draw(t_beta *beta, t_dda *dda)
{
	dda->dx = fabs((dda->start_x + dda->m_x) - dda->end_x);
	dda->dy = fabs((dda->start_y + dda->m_y) - dda->end_y);
	dda->max = fmax(dda->dx, dda->dy);
	dda->dx = dda->dx / dda->max;
	dda->dy = dda->dy / dda->max;
	while (dda->max-- > 0)
	{
		my_mlx_pixel_put(&beta->image, dda->start_x, dda->start_y, dda->color);
		dda->start_x += dda->dx;
		dda->start_y += dda->dy;
	}
}
