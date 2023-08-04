/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fold_of_view.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:44:03 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:44:16 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fold_of_view(t_beta *beta)
{
	if (beta->__angle_start <= beta->_const)
	{
		beta->__angle_start += ABR;
		if (beta->__angle_start > 2 * PI)
			beta->__angle_start -= 2 * PI;
		beta->_pdx = cos(beta->__angle_start);
		beta->_pdy = sin(beta->__angle_start);
	}
	else
	{
		beta->__angle_start += ABR;
		if (beta->__angle_start < 0)
			beta->__angle_start += 2 * PI;
		beta->_pdx = cos(beta->__angle_start);
		beta->_pdy = sin(beta->__angle_start);
	}
}
