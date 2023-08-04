/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:21:08 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 19:35:14 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_beta *beta)
{
	if (keycode == 99999)
	{
		beta->pdx = cos(30 * 0.0174532925);
		beta->pdy = sin(30 * 0.0174532925);
		beta->shift_y += beta->pdy * 5;
		beta->shift_x += beta->pdx * 5;
		beta->pdx = cos(beta->_const);
		beta->pdy = sin(beta->_const);
	}
	esc(beta, keycode);
	mouvement(beta, keycode);
	_fold_of_view(beta, keycode);
	mlx_clear_window(beta->mlx, beta->win);
	bzero(beta->world.addr, sizeof(int) * (SCREENWIDTH) * SCREENHEIGHT);
	backgrand(beta);
	randring(beta);
	mlx_put_image_to_window(beta->mlx, beta->win, beta->world.img, 0, 0);
	mlx_put_image_to_window(beta->mlx, beta->win, beta->image.img,
		0, SCREENHEIGHT - B * beta->map->height);
	return (0);
}
