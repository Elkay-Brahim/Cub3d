/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_world.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:26:04 by rrasezin          #+#    #+#             */
/*   Updated: 2023/08/03 20:29:05 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_border(t_map_s *map, int i, int j)
{
	while (j < map->height)
	{
		i = 0;
		while (i < map->width)
		{
			if (map->map[j][i] == 5 || map->map[j][i] == 0 \
				|| map->map[j][i] == 3)
			{
				if (!(j > 0 && j < (map->height - 1) && i > 0 \
					&& i < (map->width - 1)))
					return (1);
				if ((j > 0 && map->map[j - 1][i] == 2) || \
					(j < (map->height - 1) && map->map[j + 1][i] == 2))
					return (1);
				if ((i > 0 && map->map[j][i - 1] == 2) || \
					(i < (map->width - 1) && map->map[j][i + 1] == 2))
					return (1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

int	check_content(char *line, int *d)
{
	int	i;
	int	dir;

	i = 0;
	dir = 0;
	while (line[i] != '\0')
	{
		if (!(line[i] == '1' || line[i] == '0' || line[i] == 'D' \
			|| line[i] == '\n' || line[i] == ' '))
		{
			if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'W'\
				|| line[i] == 'E') && dir == 0)
				dir = line[i];
			else
				return (1);
		}
		i++;
	}
	if (dir == 0)
		return (1);
	*d = dir;
	return (0);
}

int	check_map(t_map_s *map, char *line)
{
	int		i;
	char	**map_2d;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n' && line[i + 1] == '\n')
			break ;
		i++;
	}
	while (line[i] && line[i] == '\n')
		i++;
	if (line[i] != '\0' || check_content(line, &map->direction) != 0)
	{
		write (2, "additonal data\n", 15);
		return (1);
	}
	map_2d = ft_split(line, '\n');
	final_map(map, map_2d);
	free_double(map_2d);
	if (check_border(map, 0, 0) != 0)
		return (1);
	return (0);
}

int	get_world(t_line *data, t_map_s *map)
{
	char	*map_line;

	if (data != NULL)
	{
		map_line = ft_calloc(1, 1);
		while (data != NULL)
		{
			map_line = ft_strjoin(map_line, data->line);
			data = data->next;
		}
		if (!map_line || check_map(map, map_line) != 0)
		{
			free(map_line);
			return (1);
		}
	}
	else
	{
		write (2, "-_- there is no world here\n", 27);
		return (1);
	}
	free(map_line);
	return (0);
}
