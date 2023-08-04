/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state_door.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:24:40 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:24:53 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_state_door(t_beta *beta, int keycode)
{
	if (keycode == 126 && beta->map->map[(int)(beta->pos_py / B)]
		[(int)(beta->pos_px / B)] != 3)
	{
		beta->door = true;
	}
	if (keycode == 125)
	{
		beta->door = false;
		time(&beta->start_time);
	}
}
