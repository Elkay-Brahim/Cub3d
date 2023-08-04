/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:27:04 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 19:11:58 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	up_down(t_beta *beta, int keycode)
{
	int	x;
	int	y;
	int	x1;
	int	y1;

	if (keycode == 13)
	{
		x = (int)(((beta->player_x * B + beta->shift_x - beta->pdx * 3) / B));
		y = (int)(((beta->player_y * B + beta->shift_y - beta->pdy * 3) / B));
		x1 = (int)(((beta->player_x * B + beta->shift_x - beta->pdx * 5) / B));
		y1 = (int)(((beta->player_y * B + beta->shift_y - beta->pdy) / B));
	}
	if (keycode == 1)
	{
		x = (int)(((beta->player_x * B + beta->shift_x + beta->pdx * 3) / B));
		y = (int)(((beta->player_y * B + beta->shift_y + beta->pdy * 3) / B));
		x1 = (int)(((beta->player_x * B + beta->shift_x + beta->pdx * 5) / B));
		y1 = (int)(((beta->player_y * B + beta->shift_y + beta->pdy) / B));
	}
	if ((beta->map->map[y][x] == 0 && beta->map->map[y1][x1] == 0))
		return (0);
	return (-1);
}
