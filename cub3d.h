/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 10:37:17 by bchifour          #+#    #+#             */
/*   Updated: 2023/07/29 13:17:28 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define screenHeight 560
#define screenWidth 1360
#define mapWidth 24
#define mapHeight 24
#define B 40

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> // must be remouv
#include <unistd.h> // must be remouv
#include <stdio.h> // must be remouv

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map
{
	int **map;
	int width;
	int height;
}		t_map;

typedef struct s_beta
{
	void	*mlx;
	void	*win;
	t_data	image;
	t_data	image3D;
	t_map	*map;
	t_map	*textur;
	float	_const;
	float	pdx;
	float	pdy;
	float	shift_x;
	float	shift_y;
	int		player_x;
	int		player_y;
	int		i; //must be map->width
	int		y; //must be map->height
	
	
	char	**textur_path;
}		t_beta;

typedef struct s_dda
{
	float	start_x;
	float	start_y;
	float	end_x;
	float	end_y;
	float	dx;
	float	dy;
	float	max;
	float	x;
	float	y;
	
	int		m_x;
	int		m_y;
	int		color;
}		t_dda;

#endif