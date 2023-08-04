/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 09:43:40 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 19:36:20 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_init(t_beta *beta, t_map_s *first)
{
	beta->mlx = mlx_init();
	beta->win = mlx_new_window(beta->mlx, SCREENWIDTH, SCREENHEIGHT, "CUB3D");
	beta->image.img = mlx_new_image(beta->mlx, B * first->width,
			B * first->height);
	beta->image.addr = mlx_get_data_addr(beta->image.img,
			&beta->image.bits_per_pixel,
			&beta->image.line_length, &beta->image.endian);
	beta->world.img = mlx_new_image(beta->mlx, SCREENWIDTH, SCREENHEIGHT);
	beta->world.addr = mlx_get_data_addr(beta->world.img,
			&beta->world.bits_per_pixel,
			&beta->world.line_length, &beta->world.endian);
	init_beta(beta, first);
	backgrand(beta);
	key_hook(99999, beta);
	mlx_put_image_to_window(beta->mlx, beta->win, beta->world.img, 0, 0);
	mlx_put_image_to_window(beta->mlx, beta->win, beta->image.img, 0,
		SCREENHEIGHT - B * beta->map->height);
	mlx_key_hook(beta->win, key_hook, beta);
	mlx_hook(beta->win, 2, 0, key_hook, beta);
	mlx_loop(beta->mlx);
	return (0);
}
