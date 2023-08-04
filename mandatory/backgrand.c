/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backgrand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:27:47 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 18:27:32 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	backgrand(t_beta *beta)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < SCREENHEIGHT - 1)
	{
		x = 0;
		if (y < SCREENHEIGHT / 2)
			color = beta->c_color;
		else
			color = beta->f_color;
		while (x < SCREENWIDTH - 1)
		{
			my_mlx_pixel_put(&beta->world, x, y, color);
			x++;
		}
		y++;
	}
	return ;
}
