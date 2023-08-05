/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:51:16 by rrasezin          #+#    #+#             */
/*   Updated: 2023/08/05 10:38:48 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_beta *beta, t_dda *line, t_cord p2)
{
	line->m_y = fabs((beta->textur[beta->textur_i].height - 1) \
		- ((beta->textur[beta->textur_i].height \
			* (fabs(p2.y - line->start_y))) / line->max));
	if (line->start_y >= 0 && line->start_y < SCREENHEIGHT \
		&& line->start_x < SCREENWIDTH)
		my_mlx_pixel_put(&beta->world, line->start_x, line->start_y, \
			beta->textur[beta->textur_i].map[line->m_y][line->m_x]);
	line->start_x += line->end_x;
	line->start_y += line->end_y;
}

void	draw_textur(t_beta *beta, t_cord p1, t_cord p2)
{
	t_dda	line;
	int		i;

	i = 0;
	line.dx = p1.x - p2.x;
	line.dy = p1.y - p2.y;
	line.max = fmax(fabs(line.dx), fabs(line.dy));
	line.end_x = fabs(line.dx) / line.max;
	line.end_y = fabs(line.dy) / line.max;
	line.start_x = p1.x;
	line.start_y = p1.y;
	if (beta->inter_wall_side == WALL_SIDE_Y)
		line.m_x = (beta->textur[beta->textur_i].width / B) \
			* (beta->intersect_x - ((int)(beta->intersect_x / B) * B));
	else
		line.m_x = (beta->textur[beta->textur_i].width / B) \
			* (beta->intersect_y - ((int)(beta->intersect_y / B) * B));
	while (i < line.max)
	{
		put_pixel(beta, &line, p2);
		i++;
	}
	return ;
}

void	draw_wall(t_beta *beta)
{
	t_cord	p1;
	t_cord	p2;
	float	middel;
	float	ca;

	ca = beta->_const - beta->__angle_start;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	beta->__des = (beta->__des * cos(ca));
	p1.x = beta->wall_x;
	p2.x = beta->wall_x;
	p2.y = ((B * WALL) / beta->__des);
	middel = p2.y / 2;
	p1.y = (SCREENHEIGHT / 2) - middel;
	p2.y = SCREENHEIGHT / 2 + middel;
	draw_textur(beta, p1, p2);
}
