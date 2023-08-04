/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:19:44 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 18:27:33 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_door(t_beta *beta)
{
	time_t	current_time;

	if (beta->door == false)
	{
		time(&current_time);
		if (current_time - beta->start_time >= 3)
		{
			if (beta->map->map[(int)(beta->pos_py / B)]
				[(int)(beta->pos_px / B)] == 3)
				time(&beta->start_time);
			else
			{
				beta->door = true;
				mlx_clear_window(beta->mlx, beta->win);
				backgrand(beta);
				randring(beta);
				mlx_put_image_to_window(beta->mlx, beta->win,
					beta->world.img, 0, 0);
				mlx_put_image_to_window(beta->mlx, beta->win, beta->image.img,
					0, SCREENHEIGHT - B * beta->map->height);
			}
		}
	}
	return (0);
}
