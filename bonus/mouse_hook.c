/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:18:53 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 20:01:47 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_hook(int x, int y, t_beta *beta)
{
	(void)y;
	if (x < 0 || x > SCREENWIDTH)
		return (0);
	beta->_const = (x * 2 * PI) / SCREENWIDTH;
	beta->pdx = cos(beta->_const);
	beta->pdy = sin(beta->_const);
	mlx_clear_window(beta->mlx, beta->win);
	backgrand(beta);
	randring(beta);
	mlx_put_image_to_window(beta->mlx, beta->win, beta->world.img, 0, 0);
	mlx_put_image_to_window(beta->mlx, beta->win, beta->image.img,
		0, SCREENHEIGHT - B * beta->map->height);
	return (0);
}
