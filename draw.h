/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:51:48 by rrasezin          #+#    #+#             */
/*   Updated: 2023/07/28 17:44:51 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
#define DRAW_H

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define PI 3.14159265359
#define mapWidth 24
#define mapHeight 24
#define WALL 560
#define screenHeight 560
#define screenWidth 1360
#define B 40

#define WALL_SIDE_X 1
#define WALL_SIDE_Y 2

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


typedef struct s_beta{
	t_data image;
	void *mlx;
	void *win;
	int p_x;
	int p_y;
	int i;
	int y;
	float shfit_x;
	float shfit_y;
	float pdx;

	int	  inter_wall_side;
	int	  inter_wall_side1;
	int **map_color;
	t_data textur;
	int	textur_width;
	int textur_height;
	float pos_px;
	float pos_py;
	float __des;
	float intersect_x;
	float intersect_y;
    float shift_wall_x; // shift by 3;
    float wall_x;
	t_data image3D;
    float save;
	int		color;
	
	// intersaction sprits
	float sprits_x_inter;
	float sprits_y_inter;
	float sprits;
	

	

	float rx;
	float ry;

	float pdy;
	float _const;
}		t_beta;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    draw_wall(t_beta *beta);
#endif