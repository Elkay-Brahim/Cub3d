/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:45:38 by rrasezin          #+#    #+#             */
/*   Updated: 2023/08/05 10:46:21 by rrasezin         ###   ########.fr       */
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
