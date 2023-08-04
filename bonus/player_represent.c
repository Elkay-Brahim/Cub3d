/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_represent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:29:14 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:29:31 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_represent(t_beta *beta)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		my_mlx_pixel_put(&beta->image, \
			(((beta->player_x * B) + i) + beta->shift_x) - 5, \
			(((beta->player_y * B)) + beta->shift_y) - 5, 0xff0000);
		my_mlx_pixel_put(&beta->image, \
			(((beta->player_x * B)) + beta->shift_x) - 5, \
			(((beta->player_y * B) + i) + beta->shift_y) - 5, 0xff0000);
		my_mlx_pixel_put(&beta->image, \
			((((beta->player_x * B) + 10) - i) + beta->shift_x) - 5, \
			(((beta->player_y * B) + 10) + beta->shift_y) - 5, 0xff0000);
		my_mlx_pixel_put(&beta->image, \
			(((beta->player_x * B) + 10) + beta->shift_x) - 5, \
			((((beta->player_y * B) + 10) - i) + beta->shift_y) - 5, 0xff0000);
		i++;
	}
}
