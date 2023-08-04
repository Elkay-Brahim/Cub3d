/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:24:07 by rrasezin          #+#    #+#             */
/*   Updated: 2023/08/03 20:38:10 by rrasezin         ###   ########.fr       */
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
		write(2, "Error extention\n", 15);
		return (-1);
	}
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error read map\n", 15);
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

t_map_s	*littel_world(char *map_path)
{
	int			fd;
	t_line		*base_line;
	t_line		*tmp;
	t_map_s		*map;

	fd = check_file(map_path);
	if (fd == -1)
		return (NULL);
	base_line = get_data_map(fd);
	if (base_line == NULL)
	{
		write(2, "empty file\n", 11);
		close(fd);
		return (NULL);
	}
	tmp = base_line;
	map = get_map(tmp);
	change_direction(map);
	free_line(base_line);
	return (map);
}

// void	print_map_s(t_map_s *map)
// {
//     int	i = 0;
//     int	j = 0;

// 	printf("NO : %s\n", map->n_path);
// 	printf("SO : %s\n", map->s_path);
// 	printf("WE : %s\n", map->w_path);
// 	printf("EA : %s\n", map->e_path);
// 	printf("F : %d\n", map->f_color);
// 	printf("C : %d\n", map->c_color);
// 	printf("Deriction : %c\n", map->direction);
// 	printf("width : %d\n", map->width);
// 	printf("height : %d\n", map->height);
// 	printf("player : (%d, %d)\n", map->player_x, map->player_y);
// 	while (j < map->height)
// 	{
// 		printf ("[ ");
// 		while (i < map->width)
// 		{
// 			printf ("%d, ", map->map[j][i]);
// 			i++;
// 		}
// 		i = 0;
// 		j++;
// 		printf("]\n");
// 	}
// }