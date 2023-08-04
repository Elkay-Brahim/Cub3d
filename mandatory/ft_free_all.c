/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:23:13 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 17:23:28 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_all(t_beta *beta)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < beta->map->height)
	{
		free(beta->map->map[i]);
		i++;
	}
	free(beta->map->map);
	free(beta->map);
	while (j < 5)
	{
		i = 0;
		while (i < beta->textur[j].height)
		{
			free(beta->textur[j].map[i]);
			i++;
		}
		free(beta->textur[j].map);
		j++;
	}
	free(beta->textur);
	free_double(beta->textur_path);
}
