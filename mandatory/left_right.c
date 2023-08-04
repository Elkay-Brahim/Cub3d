/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:26:28 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 19:12:26 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	left_right(t_beta *beta, int keycode)
{
	int	x;
	int	y;
	int	x1;
	int	y1;

	if (keycode == 0)
	{
		x = (int)(((beta->player_x * B + beta->shift_x - beta->pdy * 3) / B));
		y = (int)(((beta->player_y * B + beta->shift_y + beta->pdx * 3) / B));
		x1 = (int)(((beta->player_x * B + beta->shift_x - beta->pdy * 5) / B));
		y1 = (int)(((beta->player_y * B + beta->shift_y + beta->pdx) / B));
	}
	if (keycode == 2)
	{
		x = (int)(((beta->player_x * B + beta->shift_x + beta->pdy * 3) / B));
		y = (int)(((beta->player_y * B + beta->shift_y - beta->pdx * 3) / B));
		x1 = (int)(((beta->player_x * B + beta->shift_x + beta->pdy * 5) / B));
		y1 = (int)(((beta->player_y * B + beta->shift_y - beta->pdx) / B));
	}
	if ((beta->map->map[y][x] == 0 && beta->map->map[y1][x1] == 0))
		return (0);
	return (-1);
}
