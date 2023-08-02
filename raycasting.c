/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:49:33 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/02 11:39:03 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	_dda(t_beta *beta)
{
	t_dda *dda;
	dda = calloc(1, sizeof(t_dda));
	
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
	while(dda->max-- > 0)
	{
		my_mlx_pixel_put(&beta->image, dda->start_x, dda->start_y, dda->color);
		dda->start_x += dda->dx;
		dda->start_y += dda->dy;
	}
	free(dda);
}

void raycasting(t_beta *beta)
{
	int __j;
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
	while (beta->__angle_start <= beta->__angle_end)
	{

		//-------fold of vew
		if (beta->__angle_start <= beta->_const)
		 {
			beta->__angle_start += ABR;
			if(beta->__angle_start > 2 * PI)
				beta->__angle_start -= 2 * PI;
			beta->_pdx = cos(beta->__angle_start);
			beta->_pdy = sin(beta->__angle_start);
		 }
		 else
		 {
			beta->__angle_start += ABR;
			if (beta->__angle_start < 0)
				beta->__angle_start += 2 * PI;
			beta->_pdx = cos(beta->__angle_start);
			beta->_pdy = sin(beta->__angle_start);
		 }

		 //-----calcul destance of x
		 __j = 1;
		 while(1)
		 {
			if ((beta->__angle_start * 180)/PI > 90 && (beta->__angle_start * 180)/PI < 270)
			{
				beta->dx = beta->pos_px - (int)((beta->pos_px / B) + __j ) * B;
				beta->new_des_x = (beta->dx / cos(beta->__angle_start)) + 0.001;
			}
			else
			{
				beta->dx = beta->pos_px - (int)((beta->pos_px / B) + 1 - __j) * B;
				beta->new_des_x = (beta->dx / cos(beta->__angle_start)) + 0.001;
			}
			//----breaks of x
			beta->i = ((int)(beta->player_x*B+beta->shift_x - beta->_pdx * beta->new_des_x)/B);
			beta->y = ((int)(beta->player_y*B+beta->shift_y - beta->_pdy * beta->new_des_x)/B);
			if (beta->y <= 0 || beta->y > beta->map->height - 1 || beta->i <= 0 || beta->i > beta->map->width - 1)
				break;
			if (beta->map->map[beta->y][beta->i] == 1 || beta->map->map[beta->y][beta->i] == 3)
			{
				if (beta->map->map[beta->y][beta->i] == 3)
					beta->new_des_x = beta->new_des_x;
				break;
			}
			if (beta->map->map[beta->y][beta->i] == 0)
			{
				if (((beta->__angle_start * 180)/PI  > 0 && (beta->__angle_start * 180)/PI  < 90 )|| (beta->__angle_start * 180)/PI  > 360)
				{
					if ( beta->map->map[beta->y + 1][beta->i] == 1 && beta->map->map[beta->y][beta->i + 1] == 1)
						break;
				}
				else if ((beta->__angle_start * 180)/PI  > 90 && (beta->__angle_start * 180)/PI  < 180)
				{
					if ( beta->map->map[beta->y + 1][beta->i] == 1  && beta->map->map[beta->y][beta->i-1] == 1)
						break;
				}
				else if ((beta->__angle_start * 180)/PI  > 180 && (beta->__angle_start * 180)/PI  < 270)
				{
					if ( beta->map->map[beta->y - 1][beta->i] == 1  && beta->map->map[beta->y][beta->i-1] == 1)
						break;
				}
				else if ((beta->__angle_start * 180)/PI  > 270 && (beta->__angle_start * 180)/PI  < 360)
				{
					if ( beta->map->map[beta->y - 1][beta->i] == 1  && beta->map->map[beta->y][beta->i + 1] == 1)
						break;
				}
			}
			
			__j++;
		 }
		 //-----calcul destance of y
		 __j = 1;
		 while(1)
		 {
			if (((beta->__angle_start * 180)/PI) > 180 && ((beta->__angle_start * 180)/PI) < 360)
			{
				beta->dy = beta->pos_py - (int)((beta->pos_py / B) + __j ) * B;
				beta->new_des_y = (beta->dy / sin(beta->__angle_start)) + 0.001;
			}
			else
			{
				beta->dy = beta->pos_py - (int)((beta->pos_py / B) + 1 - __j)  * B;
				beta->new_des_y = (beta->dy / sin(beta->__angle_start)) + 0.001;
			}
			//----breaks of y
			beta->i = ((int)(beta->player_x*B+beta->shift_x - beta->_pdx * beta->new_des_y)/B);
			beta->y = ((int)(beta->player_y*B+beta->shift_y - beta->_pdy * beta->new_des_y)/B);
			if (beta->y <= 0 || beta->y > beta->map->height - 1 || beta->i <= 0 || beta->i > beta->map->width - 1)
				break;
			if (beta->map->map[beta->y][beta->i] == 1 || beta->map->map[beta->y][beta->i] == 3)
			{
				if (beta->map->map[beta->y][beta->i] == 3)
					beta->new_des_y = beta->new_des_y;
				break;
			}
			if (beta->map->map[beta->y][beta->i] == 0)
			{
				if (((beta->__angle_start * 180)/PI  > 0 && (beta->__angle_start * 180)/PI  < 90 )|| (beta->__angle_start * 180)/PI  > 360)
				{
					if ( beta->map->map[beta->y + 1][beta->i] == 1 && beta->map->map[beta->y][beta->i + 1] == 1)
						break;
				}
				else if ((beta->__angle_start * 180)/PI  > 90 && (beta->__angle_start * 180)/PI  < 180)
				{
					if ( beta->map->map[beta->y + 1][beta->i] == 1  && beta->map->map[beta->y][beta->i-1] == 1)
						break;
				}
				else if ((beta->__angle_start * 180)/PI  > 180 && (beta->__angle_start * 180)/PI  < 270)
				{
					if ( beta->map->map[beta->y - 1][beta->i] == 1  && beta->map->map[beta->y][beta->i-1] == 1)
						break;
				}
				else if ((beta->__angle_start * 180)/PI  > 270 && (beta->__angle_start * 180)/PI  < 360)
				{
					if ( beta->map->map[beta->y - 1][beta->i] == 1  && beta->map->map[beta->y][beta->i + 1] == 1)
						break;
				}
			}
			__j++;
		 }

		 //----get min destance and intersection
		if (fabs(beta->new_des_x) < fabs(beta->new_des_y))
		{
			beta->__des = fabs(beta->new_des_x);
			if (beta->__des < 1)
				beta->__des = 1;
			beta->inter_wall_side = WALL_SIDE_X;
		}
		else
		{
			beta->__des = fabs(beta->new_des_y);
			beta->inter_wall_side = WALL_SIDE_Y;
		}
		beta->intersect_x = ((beta->pos_px - beta->_pdx * beta->__des));
		beta->intersect_y = ((beta->pos_py - beta->_pdy * beta->__des));

		//---dda
		_dda(beta);
		// printf("beta->wall %f\n", beta->wall_x);
		draw_wall(beta);
		beta->wall_x += 1;
	}
}