/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:28:27 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 18:09:17 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	randring(t_beta *beta)
{
	int	i;
	int	y;
	int	x;

	y = -1;
	while (++y < beta->map->height)
	{
		i = -1;
		while (++i < beta->map->width)
		{
			x = -1;
			while (++x <= B)
				draw_line(beta, i, y, x);
		}
	}
	player_represent(beta);
	raycasting(beta, -1);
}
