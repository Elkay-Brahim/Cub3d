/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:31:07 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:31:20 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color(t_beta *beta, int y, int i)
{
	int	color;

	if (beta->map->map[y][i] == 1)
		color = 0x00a86b;
	else if (beta->map->map[y][i] == 3)
		color = 0xfff000;
	else
		color = 0x000000;
	return (color);
}
