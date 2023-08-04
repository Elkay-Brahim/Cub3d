/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:23:55 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:24:11 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouvement(t_beta *beta, int keycode)
{
	if (keycode == 13 && up_down(beta, keycode) == 0)
	{
		beta->shift_y -= beta->pdy * 1.5;
		beta->shift_x -= beta->pdx * 1.5;
	}
	if (keycode == 1 && up_down(beta, keycode) == 0)
	{
		beta->shift_y += beta->pdy * 1.5;
		beta->shift_x += beta->pdx * 1.5;
	}
	if (keycode == 0 && left_right(beta, keycode) == 0)
	{
		beta->shift_x -= beta->pdy * 1.5;
		beta->shift_y += beta->pdx * 1.5;
	}
	if (keycode == 2 && left_right(beta, keycode) == 0)
	{
		beta->shift_x += beta->pdy * 1.5 ;
		beta->shift_y -= beta->pdx * 1.5;
	}
}
