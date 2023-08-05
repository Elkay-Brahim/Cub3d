/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:45:55 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/05 13:32:15 by rrasezin         ###   ########.fr       */
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
			write(2, "Error\nthe map is so large\n", 26);
			return (1);
		}
		if (first == NULL)
		{
			write (2, "Error\n", 6);
			return (1);
		}
		beta = ft_calloc(sizeof(t_beta), 1);
		ft_init(beta, first);
	}
	else
		write(2, "Error\n", 6);
	return (0);
}
