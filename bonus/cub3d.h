/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 10:37:17 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/05 10:46:38 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCREENHEIGHT 1000
# define SCREENWIDTH 1360
# define B 10
# define PI M_PI
# define WALL 560
# define WALL_SIDE_X 1
# define WALL_SIDE_Y 2
# define TEXTUR_W 0
# define TEXTUR_N 1
# define TEXTUR_E 2
# define TEXTUR_S 3
# define TEXTUR_D 4

// Angle Between Rays
# define ABR 0.00077

# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdbool.h>
# include <time.h>
# include "parsing_map/parsing.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map
{
	int	**map;
	int	width;
	int	height;
}		t_map;

typedef struct s_beta
{
	void	*mlx;
	void	*win;
	t_data	image;
	t_data	world;
	t_map	*map;
	t_map	*textur;
	int		f_color;
	int		c_color;
	float	_const;
	int		textur_i;
	float	pdx;
	float	pdy;
	float	__des;
	int		inter_wall_side;
	float	wall_x;
	float	_pdx;
	float	_pdy;
	float	_angle;
	float	__angle_start;
	float	__angle_end;
	float	pos_px;
	float	pos_py;
	float	new_des_x;
	float	new_des_y;
	float	intersect_x;
	float	intersect_y;
	float	dx;
	float	dy;
	time_t	current_time;
	time_t	start_time;
	int		door_check;
	bool	door;
	float	shift_x;
	float	shift_y;
	int		player_x;
	int		player_y;
	int		i;
	int		y;
	t_map_s	*first;
	char	**textur_path;
}		t_beta;

typedef struct s_cord
{
	float	x;
	float	y;
}		t_cord;

typedef struct s_dda
{
	float	start_x;
	float	start_y;
	float	end_x;
	float	end_y;
	float	dx;
	float	dy;
	float	max;
	int		m_x;
	int		m_y;
	int		color;
}		t_dda;

void	raycasting(t_beta *beta, int __j);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_wall(t_beta *beta);
void	init_beta(t_beta *beta, t_map_s *first);
int		up_down(t_beta *beta, int keycode);
int		ray_effect_y(t_beta *beta, float angle, int **m);
int		ray_effect_x(t_beta *beta, float angle, int **m);
void	randring(t_beta *beta);
void	player_represent(t_beta *beta);
void	mouvement(t_beta *beta, int keycode);
int		mouse_hook(int x, int y, t_beta *beta);
int		left_right(t_beta *beta, int keycode);
int		key_hook(int keycode, t_beta *beta);
void	init_env_raycasting(t_beta *beta);
void	init_beta(t_beta *beta, t_map_s *first);
void	get_destance(t_beta *beta, float angle);
void	ft_textur(t_beta *beta, t_map_s *map);
int		ft_init(t_beta *beta, t_map_s *first);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_free_all(t_beta *beta);
void	fold_of_view(t_beta *beta);
void	esc(t_beta *beta, int keycode);
void	draw_line(t_beta *beta, int i, int y, int x);
void	dda_draw(t_beta *beta, t_dda *dda);
int		color(t_beta *beta, int y, int i);
int		close_door(t_beta *beta);
void	check_state_door(t_beta *beta, int keycode);
void	calcul_destance_y(t_beta *beta, int __j);
void	calcul_destance_x(t_beta *beta, int __j);
int		break_of_y(t_beta *beta);
int		break_of_x(t_beta *beta);
void	backgrand(t_beta *beta);
void	_fold_of_view(t_beta *beta, int keycode);
void	_dda(t_beta *beta);
int		cross_window(t_beta *beta);

#endif