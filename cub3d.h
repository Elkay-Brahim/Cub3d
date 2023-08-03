/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 10:37:17 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/03 15:03:57 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define screenHeight 800
#define screenWidth 1360
#define mapWidth 24
#define mapHeight 24
#define B 10
#define PI 3.14159265359
#define WALL 560
#define ABR 0.00077 // Angle Between Rays


#define WALL_SIDE_X 1
#define WALL_SIDE_Y 2

#define TEXTUR_W 0
#define TEXTUR_N 1
#define TEXTUR_E 2
#define TEXTUR_S 3

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include "parsing_map/parsing.h"
#include <string.h> // must be remouv
#include <unistd.h> // must be remouv
#include <stdio.h> // must be remouv
#include <stdbool.h> // check after push
#include <time.h>

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
	int		f_color;
	int		c_color;
	float	_const;
	int		textur_i;
	float	pdx;
	float	pdy;
	//------raycasting------
	float __des;
	int inter_wall_side;
	float wall_x;
	float	_pdx;
	float	_pdy;
	float	_angle;
	float __angle_start;
	float __angle_end;
	float pos_px;
	float pos_py;
	float new_des_x;
	float new_des_y;
	float intersect_x;
	float intersect_y;
	float dx;
	float dy;
	time_t	current_time;
	time_t	start_time;
	//-------keyhook-----
	int index;
	bool door;
	
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

int worldMap[mapWidth][mapHeight];


void raycasting(t_beta *beta);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    draw_wall(t_beta *beta);
#endif