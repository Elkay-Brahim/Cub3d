/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 20:16:47 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 20:18:15 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cross_window(t_beta *beta)
{
	ft_free_all(beta);
	mlx_destroy_window(beta->mlx, beta->win);
	free(beta->first);
	free(beta);
	exit(1);
}
