/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:34:58 by rrasezin          #+#    #+#             */
/*   Updated: 2023/08/03 20:35:58 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	tack_element(t_map_s *map, char *line, int size, int i)
{
	int	tmp;

	tmp = -1;
	while (++tmp < map->width)
	{
		if (tmp < size)
		{
			if (line[tmp] && line[tmp] == '1')
				map->map[i][tmp] = 1;
			else if (line[tmp] && line[tmp] == '0')
				map->map[i][tmp] = 0;
			else if (line[tmp] && line[tmp] == ' ')
				map->map[i][tmp] = 2;
			else if (line[tmp] && line[tmp] == 'D')
				map->map[i][tmp] = 3;
			else if (line[tmp] && line[tmp] == map->direction)
			{
				map->map[i][tmp] = 0;
				map->player_x = tmp;
				map->player_y = i;
			}
		}
		else
			map->map[i][tmp] = 2;
	}
}

void	init_w_h(t_map_s *map, char **line)
{
	int	tmp;
	int	i;

	tmp = 0;
	i = 0;
	while (line[i] != NULL)
	{
		if (line[i][0] != '\n')
		{
			map->height++;
			tmp = ft_strlen(line[i]);
			if (map->width < tmp)
				map->width = tmp;
		}
		i++;
	}
	return ;
}

void	final_map(t_map_s *map, char **line)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	init_w_h(map, line);
	map->map = ft_calloc(sizeof(int *), map->height + 1);
	while (i < map->height)
	{
		if (line[j][0] != '\n')
		{
			map->map[i] = ft_calloc(sizeof(int), map->width + 1);
			size = ft_strlen(line[j]);
			tack_element(map, line[j], size, i);
			i++;
		}
		j++;
	}
}
