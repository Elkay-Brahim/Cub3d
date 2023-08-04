/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _fold_of_view.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:25:42 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:25:57 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	_fold_of_view(t_beta *beta, int keycode)
{
	if (keycode == 124)
	{
		beta->_const += 0.1;
		if (beta->_const > 2 * PI)
			beta->_const -= 2 * PI;
		beta->pdx = cos(beta->_const);
		beta->pdy = sin(beta->_const);
	}
	else if (keycode == 123)
	{
		beta->_const -= 0.1;
		if (beta->_const < 0)
			beta->_const += 2 * PI;
		beta->pdx = cos(beta->_const);
		beta->pdy = sin(beta->_const);
	}
}
