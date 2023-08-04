/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:32:25 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/04 19:21:10 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

t_map	read_textur_map(void *mlx, char *textur_path)
{
	t_map	map;
	t_data	data;
	int		i;
	int		j;

	j = 0;
	data.img = mlx_xpm_file_to_image(mlx, textur_path, &map.width, &map.height);
	data.addr = mlx_get_data_addr(data.img, \
		&data.bits_per_pixel, &data.line_length, &data.endian);
	map.map = ft_calloc(sizeof(int *), map.height);
	while (j < map.height)
	{
		i = 0;
		map.map[j] = ft_calloc(sizeof(int), map.width);
		while (i < map.width)
		{
			map.map[j][i] = get_color(&data, i, j);
			i++;
		}
		j++;
	}
	mlx_destroy_image(mlx, data.img);
	return (map);
}

void	ft_textur(t_beta *beta, t_map_s *map)
{
	int	i;

	i = 0;
	beta->textur_path = ft_calloc(sizeof(char *), 5);
	beta->textur_path[0] = map->w_path;
	beta->textur_path[1] = map->n_path;
	beta->textur_path[2] = map->e_path;
	beta->textur_path[3] = map->s_path;
	beta->textur = ft_calloc(sizeof(t_map), 4);
	while (i < 4)
	{
		beta->textur[i] = read_textur_map(beta->mlx, beta->textur_path[i]);
		i++;
	}
}
