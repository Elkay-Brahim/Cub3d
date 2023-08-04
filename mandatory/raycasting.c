/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:49:33 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 20:07:06 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_beta *beta, int __j)
{
	init_env_raycasting(beta);
	while (beta->__angle_start <= beta->__angle_end
		&& beta->wall_x < SCREENWIDTH)
	{
		fold_of_view(beta);
		__j = 0;
		while (1 && ++__j)
		{
			calcul_destance_x(beta, __j);
			if (break_of_x(beta) == -1)
				break ;
		}
		__j = 0;
		while (1 && ++__j)
		{
			calcul_destance_y(beta, __j);
			if (break_of_y(beta) == -1)
				break ;
		}
		get_destance(beta, (beta->__angle_start * 180) / PI);
		draw_wall(beta);
		beta->wall_x += 1;
	}
}
