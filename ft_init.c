/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 09:43:40 by bchifour          #+#    #+#             */
/*   Updated: 2023/08/02 18:58:19 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int worldMap[24][24] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,0,1,0,0,0,1,0,0,0,1,1,1,1,1,0,1},
  {1,0,1,1,1,1,0,0,0,0,1,0,0,1,0,0,1},
  {1,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1},
  {1,0,1,0,0,1,0,0,0,0,1,1,0,1,1,1,1},
  {1,0,1,0,0,2,0,0,0,0,1,0,0,0,0,0,1},
  {1,0,1,0,0,1,0,0,0,0,0,0,0,1,1,0,1},
  {1,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1},
  {1,0,1,0,0,0,1,1,1,1,5,0,0,1,0,0,1},
  {1,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1},
  {1,0,1,0,1,1,1,1,1,0,0,0,0,1,0,0,1},
  {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int	get_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return(*(unsigned int *)dst);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_map read_textur_map(void *mlx, char *textur_path)
{
    t_map    map;
    t_data            data;
    int                i;
    int                j;

    j = 0;
    data.img = mlx_xpm_file_to_image(mlx, textur_path, &map.width, &map.height);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    map.map = calloc(sizeof(int *), map.height);
    while (j < map.height)
    {
        i = 0;
        map.map[j] = calloc(sizeof(int), map.width);
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
	int i;

	i = 0;
	beta->textur_path = calloc(sizeof(char *), 4);
	beta->textur_path[0] = strdup(map->w_path);
	beta->textur_path[1] = strdup(map->n_path);
	beta->textur_path[2] = strdup(map->e_path);
	beta->textur_path[3] = strdup(map->s_path);
	beta->textur = calloc(sizeof(t_map), 4);
	
	while(i < 4)
	{
		beta->textur[i] = read_textur_map(beta->mlx, beta->textur_path[i]);
		i++;
	}
}



void	dda_draw(t_beta *beta, t_dda *dda)
{
	dda->dx = fabs((dda->start_x + dda->m_x) - dda->end_x);
	dda->dy = fabs((dda->start_y + dda->m_y) - dda->end_y);
	dda->max = fmax(dda->dx, dda->dy);
	dda->dx = dda->dx / dda->max;
	dda->dy = dda->dy / dda->max;
	while(dda->max-- > 0)
	{
		my_mlx_pixel_put(&beta->image, dda->start_x, dda->start_y, dda->color);
		dda->start_x += dda->dx;
		dda->start_y += dda->dy;
	}
}

int	color(t_beta *beta, int y, int i)
{
	int color;
	
	if (beta->map->map[y][i] == 1)
		color = 0x00a86b;
	else if (beta->map->map[y][i] == 3)
		color = 0xfff000;
	// else if (beta->map->map[y][i] == 3)
	// 	color = 0x0000ff;
	else
		color = 0x000000;
	return (color);
}

void	draw_line(t_beta *beta, int i, int y, int x)
{
	t_dda dda;

	dda.color = color(beta, y, i);
	dda.m_x = x;
	dda.m_y = 0;
	dda.start_x = (i * B);
	dda.start_y = y * B;
	dda.end_x = i * B;
	dda.end_y = (y + 1) * B;
	dda_draw(beta, &dda);
	dda.m_x = 0;
	dda.m_y = x;
	dda.start_x = (i * B);
	dda.start_y = (y * B) ;
	dda.end_x = (i + 1) * B;
	dda.end_y = y * B;
	dda_draw(beta, &dda);
}

void player_represent(t_beta *beta)
{
		int i = 0;
		while(i < 10)
		{
			my_mlx_pixel_put(&beta->image, (((beta->player_x * B) + i) + beta->shift_x) - 5 , (((beta->player_y * B)) + beta->shift_y) - 5 , 0xff0000);
			my_mlx_pixel_put(&beta->image, (((beta->player_x * B))+ beta->shift_x) - 5 ,(((beta->player_y * B) + i)+ beta->shift_y) - 5 , 0xff0000);
			my_mlx_pixel_put(&beta->image, ((((beta->player_x * B) + 10) - i)+ beta->shift_x ) - 5,(((beta->player_y * B) + 10) + beta->shift_y) - 5, 0xff0000);
			my_mlx_pixel_put(&beta->image, (((beta->player_x * B) + 10) + beta->shift_x) - 5 ,((((beta->player_y * B) + 10) - i) + beta->shift_y) -5, 0xff0000);
			i++;
		}
}

void	randring(t_beta *beta)
{
	int	i;
	int	y;
	int	x;

	y = -1;
	while(++y < beta->map->height)
	{
		i = -1;
		while(++i < beta->map->width)
		{
			x = -1;
			while(++x <= B)
				draw_line(beta, i, y, x);
			if (beta->map->map[y][i] == 5)
			{
				beta->player_x = i;
				beta->player_y = y;
			}
		}
	}
	player_represent(beta);
	raycasting(beta);
}

void backgrand(t_beta *beta)
{
	int x ;
	int y = 0;
	int color;
	while(y < screenHeight-1)
	{
		x = 0;
		if (y < screenHeight/2)
			color = beta->c_color;
		else
			color = beta->f_color;
		while(x < screenWidth-1)
		{
			my_mlx_pixel_put(&beta->image3D, x, y, color);
			x++;
		}
		y++;
	}
	return;
}

int check_wall(t_beta *beta, int keycode)
{
	int x;
	int y;
	int x1;
	int y1;
	if(keycode == 13)
	{
		x = (int)(((beta->player_x * B + beta->shift_x - beta->pdx*3)/B));
		y = (int)(((beta->player_y * B + beta->shift_y - beta->pdy*3) / B));
		x1 = (int)(((beta->player_x * B + beta->shift_x - beta->pdx*5)/B));
		y1 = (int)(((beta->player_y * B + beta->shift_y - beta->pdy) / B));
		
	}
	else if (keycode == 1)
	{
		x = (int)(((beta->player_x * B + beta->shift_x + beta->pdx*3)/B));
		y = (int)(((beta->player_y * B + beta->shift_y + beta->pdy*3) / B));
		x1 = (int)(((beta->player_x * B + beta->shift_x + beta->pdx*5)/B));
		y1 = (int)(((beta->player_y * B + beta->shift_y + beta->pdy) / B));
	}
	else if (keycode == 0)
	{
		x = (int)(((beta->player_x * B + beta->shift_x - beta->pdy*3)/B));
		y = (int)(((beta->player_y * B + beta->shift_y + beta->pdx*3) / B));
		x1 = (int)(((beta->player_x * B + beta->shift_x - beta->pdy* 5)/B));
		y1 = (int)(((beta->player_y * B + beta->shift_y + beta->pdx) / B));

	}
	else if (keycode == 2)
	{
		x = (int)(((beta->player_x * B + beta->shift_x + beta->pdy *3)/B));
		y = (int)(((beta->player_y * B + beta->shift_y - beta->pdx *3) / B));
		x1 = (int)(((beta->player_x * B + beta->shift_x + beta->pdy * 5)/B));
		y1 = (int)(((beta->player_y * B + beta->shift_y - beta->pdx ) / B));

	}


	if (beta->map->map[y][x] != 1 && beta->map->map[y1][x1] != 1)
		return(0);
	
	return(-1);
}


int	key_hook(int keycode, t_beta *beta)
{
	int b = 0;
		if (keycode == 99999)
		{
			beta->pdx = cos(30 * 0.0174532925);
			beta->pdy = sin(30 * 0.0174532925);
			beta->shift_y += beta->pdy * 5;
			beta->shift_x += beta->pdx * 5;
			beta->pdx = cos(beta->_const) ;
			beta->pdy = sin(beta->_const) ;
		}
		if (keycode == 13  && check_wall(beta, keycode) == 0 )
		{

			beta->shift_y -= beta->pdy * 1.5;
			beta->shift_x -= beta->pdx * 1.5;
		}
		if (keycode == 1 && check_wall(beta, keycode) == 0)
		{
			beta->shift_y += beta->pdy* 1.5;
			beta->shift_x += beta->pdx*1.5;

		}
		if (keycode == 0  && check_wall(beta, keycode) == 0 )
		{
			beta->shift_x -= beta->pdy * 1.5 ;
			beta->shift_y += beta->pdx*1.5;
			// beta->shift_x = beta->pdx * 1.5;
		}
		if (keycode == 2  && check_wall(beta, keycode) == 0)
		{
			beta->shift_x += beta->pdy * 1.5 ;
			beta->shift_y -= beta->pdx*1.5;
			// beta->shift_x = beta->pdx * 1.5;
		}
	 if (keycode == 124)
		{
			beta->_const += 0.1;
			if(beta->_const > 2 * PI)
				beta->_const -= 2 * PI;
			beta->pdx = cos(beta->_const);
			beta->pdy = sin(beta->_const);
		}
		else if (keycode == 123)
		{
			beta->_const -= 0.1;
			if (beta->_const < 0)
				beta->_const += 2 * PI;
			beta->pdx = cos(beta->_const) ;
			beta->pdy = sin(beta->_const) ;

		}

		mlx_clear_window(beta->mlx, beta->win);
		bzero(beta->image3D.addr, sizeof(int)*(screenWidth) * screenHeight );
		backgrand(beta);
		randring(beta);
		mlx_put_image_to_window(beta->mlx, beta->win, beta->image3D.img, 0, 0);
		mlx_put_image_to_window(beta->mlx, beta->win, beta->image.img, 0, screenHeight - B*14);
	return(0);
}






int	ft_init(t_beta *beta, char *arg)
{
	// parse_map(beta, arg);
	t_map_s	*first = littel_world(arg);
	if (first == NULL)
		return (1);
	beta->_const = first->direction * 0.0174532925;
	beta->pdx = cos(beta->_const);
	beta->pdy = sin(beta->_const);
	beta->i = 00, beta->y = 0, beta->shift_x = 0, beta->shift_y = 0;
	beta->mlx = mlx_init();
	beta->win = mlx_new_window(beta->mlx, screenWidth, screenHeight, "CUB3D");
	beta->image.img = mlx_new_image(beta->mlx, B*first->width, B*first->height);
	beta->image.addr = mlx_get_data_addr(beta->image.img, &beta->image.bits_per_pixel, &beta->image.line_length, &beta->image.endian);
	beta->image3D.img = mlx_new_image(beta->mlx, screenWidth , screenHeight);
	beta->image3D.addr = mlx_get_data_addr(beta->image3D.img, &beta->image3D.bits_per_pixel, &beta->image3D.line_length, &beta->image3D.endian);
	ft_textur(beta, first);
	beta->f_color = first->f_color;
	beta->c_color = first->c_color;
	backgrand(beta);
	beta->map = calloc(sizeof(t_map), 1);
	beta->map->map = first->map;
	beta->map->width = first->width ;
	beta->map->height = first->height;
	print_map_s(first);
	// randring(beta);
	key_hook(99999, beta);
	mlx_put_image_to_window(beta->mlx, beta->win, beta->image3D.img, 0, 0);
	mlx_put_image_to_window(beta->mlx, beta->win, beta->image.img, 0, screenHeight - B*14);
	mlx_key_hook(beta->win, key_hook, beta);
	mlx_hook(beta->win, 2, 0, key_hook, beta);
	mlx_loop(beta->mlx);
	return (0);
}

int main(int ac, char **av)
{
	t_beta *beta;
	
	beta = calloc(sizeof(t_beta), 1);
	return(ft_init(beta, av[1]));
}