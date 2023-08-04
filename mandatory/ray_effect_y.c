/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_effect_y.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:39:04 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:39:16 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ray_effect_y(t_beta *beta, float angle, int **m)
{
	m = beta->map->map;
	if (m[beta->y][beta->i] == 0)
	{
		if ((angle > 0 && angle < 90) || angle > 360)
		{
			if (m[beta->y + 1][beta->i] == 1 && m[beta->y][beta->i + 1] == 1)
				return (-1);
		}
		else if (angle > 90 && angle < 180)
		{
			if (m[beta->y + 1][beta->i] == 1 && m[beta->y][beta->i - 1] == 1)
				return (-1);
		}
		else if (angle > 180 && angle < 270)
		{
			if (m[beta->y - 1][beta->i] == 1 && m[beta->y][beta->i - 1] == 1)
				return (-1);
		}
		else if (angle > 270 && angle < 360)
		{
			if (m[beta->y - 1][beta->i] == 1 && m[beta->y][beta->i + 1] == 1)
				return (-1);
		}
	}
	return (1);
}
