/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:24:07 by rrasezin          #+#    #+#             */
/*   Updated: 2023/08/05 13:27:01 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_double(char **sp)
{
	int	i;

	i = 0;
	while (sp[i] != NULL)
	{
		free(sp[i]);
		i++;
	}
	free(sp);
}

int	check_file(char *map_path)
{
	int	fd;

	if (check_ext(map_path, ".cub") != 0)
	{
		write(2, "Error\nextention\n", 16);
		return (-1);
	}
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nread map\n", 15);
		return (-1);
	}
	return (fd);
}

void	change_direction(t_map_s *map)
{
	if (map)
	{
		if (map->direction == 'W')
			map->direction = 0;
		else if (map->direction == 'N')
			map->direction = 90;
		else if (map->direction == 'E')
			map->direction = 180;
		else
			map->direction = 270;
	}
	return ;
}

t_map_s	*littel_world(char *map_path, int fd)
{
	t_line		*base_line;
	t_line		*tmp;
	t_map_s		*map;

	fd = check_file(map_path);
	if (fd == -1)
		return (NULL);
	base_line = get_data_map(fd);
	if (base_line == NULL)
	{
		write(2, "Error\nempty file\n", 17);
		close(fd);
		return (NULL);
	}
	tmp = base_line;
	map = get_map(tmp);
	change_direction(map);
	free_line(base_line);
	return (map);
}
