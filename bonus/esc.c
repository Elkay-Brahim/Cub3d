/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:22:28 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:22:44 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	esc(t_beta *beta, int keycode)
{
	(void)beta;
	if (keycode == 53)
	{
		ft_free_all(beta);
		mlx_destroy_window(beta->mlx, beta->win);
		free(beta->first);
		free(beta);
		exit(1);
	}
}
