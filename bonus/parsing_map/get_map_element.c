/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:12:11 by rrasezin          #+#    #+#             */
/*   Updated: 2023/08/05 13:21:28 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	rgb_to_int(char *color, int nb)
{
	char	**rgb;
	int		int_color;
	int		i;
	int		p;

	i = 0;
	int_color = 0;
	p = 0;
	if (color[ft_strlen(color) - 1] == ',')
		return (-1);
	rgb = ft_split(color, ',');
	while (rgb[i] != NULL)
	{
		nb = mini_atoi(rgb[i]);
		if (nb == -1 || i > 2)
		{
			free_double(rgb);
			return (-1);
		}
		int_color = (int_color << p) + nb;
		p = 8;
		i++;
	}
	free_double(rgb);
	return (int_color);
}

int	check_color(t_map_s *map, char **sp)
{
	if (ft_strlen(sp[0]) == 1 && sp[1] != NULL && sp[2] == NULL)
	{
		if (sp[0][0] == 'F' && map->f_color == -2)
			map->f_color = rgb_to_int(sp[1], 0);
		else if (sp[0][0] == 'C' && map->c_color == -2)
			map->c_color = rgb_to_int(sp[1], 0);
		else
		{
			write(2, "Error\ninvalid color identifier\n", 31);
			return (1);
		}
	}
	else
	{
		write(2, "Error\ninvalid color values\n", 27);
		return (1);
	}
	if (map->f_color == -1 || map->c_color == -1)
	{
		write(2, "Error\ninvalid color value\n", 26);
		return (1);
	}
	return (0);
}

int	check_path(t_map_s *map, char **sp)
{
	if (ft_strlen(sp[0]) == 2 && sp[1] != NULL && sp[2] == NULL)
	{
		if (sp[0][0] == 'N' && sp[0][1] == 'O' && !map->n_path)
			map->n_path = ft_strdup(sp[1]);
		else if (sp[0][0] == 'S' && sp[0][1] == 'O' && !map->s_path)
			map->s_path = ft_strdup(sp[1]);
		else if (sp[0][0] == 'W' && sp[0][1] == 'E' && !map->w_path)
			map->w_path = ft_strdup(sp[1]);
		else if (sp[0][0] == 'E' && sp[0][1] == 'A' && !map->e_path)
			map->e_path = ft_strdup(sp[1]);
		else if (sp[0][0] == 'D' && sp[0][1] == 'T' && !map->door)
			map->door = ft_strdup(sp[1]);
		else
		{
			write(2, "Error\ninvalid path identifier\n", 30);
			return (1);
		}
	}
	else
	{
		write(2, "Error\ninvalid path identifier\n", 30);
		return (1);
	}
	return (0);
}

int	get_map_element(t_map_s *map, char *line, int type)
{
	char	**sp;

	line[ft_strlen(line) - 1] = '\0';
	sp = ft_split(line, ' ');
	if (!sp || sp[0] == NULL)
	{
		free_double(sp);
		write (2, "Error\nwrong element\n", 20);
		return (1);
	}
	if (type == 1 && check_path(map, sp) == 1)
	{
		free_double(sp);
		return (1);
	}
	if (type == 2 && check_color(map, sp) == 1)
	{
		free_double(sp);
		return (1);
	}
	free_double(sp);
	return (0);
}
