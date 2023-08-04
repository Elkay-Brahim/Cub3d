/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw__line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:30:25 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:30:43 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_beta *beta, int i, int y, int x)
{
	t_dda	dda;

	dda.color = color(beta, y, i);
	dda.m_x = x;
	dda.m_y = 0;
	dda.start_x = (i * B);
	dda.start_y = y * B;
	dda.end_x = i * B;
	dda.end_y = (y + 1) * B;
	dda_draw(beta, &dda);
	dda.m_x = 0;
	dda.m_y = x;
	dda.start_x = (i * B);
	dda.start_y = (y * B);
	dda.end_x = (i + 1) * B;
	dda.end_y = y * B;
	dda_draw(beta, &dda);
}
