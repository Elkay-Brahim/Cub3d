/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:21:00 by rrasezin          #+#    #+#             */
/*   Updated: 2023/08/04 17:06:35 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	exist_file(t_map_s *map)
{
	int	fd;

	fd = open(map->n_path, O_RDONLY);
	if (fd == -1)
		return (1);
	close (fd);
	fd = open(map->s_path, O_RDONLY);
	if (fd == -1)
		return (1);
	close (fd);
	fd = open(map->w_path, O_RDONLY);
	if (fd == -1)
		return (1);
	close (fd);
	fd = open(map->e_path, O_RDONLY);
	if (fd == -1)
		return (1);
	close (fd);
	fd = open(map->door, O_RDONLY);
	if (fd == -1)
		return (1);
	close (fd);
	return (0);
}

int	check_ext(char *name, char *ext)
{
	int		i;
	char	*extenction;

	i = ft_strlen(name);
	if (i <= 4)
		return (1);
	extenction = name + (i - 4);
	i = 0;
	while (extenction[i])
	{
		if (extenction[i] != ext[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_data(t_map_s *map)
{
	if (map->n_path == NULL || map->s_path == NULL || map->w_path == NULL || \
		map->e_path == NULL || map->f_color == -2 || map->door == NULL || \
		map->c_color == -2)
		return (1);
	if (check_ext(map->n_path, ".xpm") == 1 || \
		check_ext(map->s_path, ".xpm") == 1 || \
		check_ext(map->w_path, ".xpm") == 1 || \
		check_ext(map->e_path, ".xpm") == 1 || \
		check_ext(map->door, ".xpm") == 1)
		return (1);
	if (exist_file(map) != 0)
		return (1);
	return (0);
}

t_map_s	*get_map(t_line *data)
{
	t_map_s	*map;

	map = ft_calloc(sizeof(t_map_s), 1);
	map->c_color = -2;
	map->f_color = -2;
	while (data->type != 3)
	{
		if (data->type != 0 && \
			get_map_element(map, data->line, data->type) != 0)
		{
			free_map(map);
			return (NULL);
		}
		data = data->next;
		if (data == NULL)
			break ;
	}
	if (check_data(map) != 0 || get_world(data, map) != 0)
	{
		free_map(map);
		write(2, "invalid path\n", 13);
		return (NULL);
	}
	return (map);
}
