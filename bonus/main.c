/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:45:55 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 18:06:56 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_beta	*beta;
	t_map_s	*first;

	if (ac == 2)
	{
		first = littel_world(av[1], 0);
		if (first && (first->width * B > SCREENWIDTH || \
			first->height * B > SCREENHEIGHT))
		{
			free_map(first);
			write(2, "the map is so large\n", 20);
			return (1);
		}
		if (first == NULL)
			return (1);
		beta = ft_calloc(sizeof(t_beta), 1);
		ft_init(beta, first);
	}
	else
		write(2, "Error\n", 6);
	return (0);
}
