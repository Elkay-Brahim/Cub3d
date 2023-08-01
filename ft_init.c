/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 09:43:40 by bchifour          #+#    #+#             */
/*   Updated: 2023/07/31 20:11:28 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int worldMap[mapWidth][mapHeight] = {
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

void	ft_textur(t_beta *beta)
{
	int i;

	i = 0;
	beta->textur_path = calloc(sizeof(char *), 4);
	beta->textur_path[0] = strdup("wall.xpm");
	beta->textur_path[1] = strdup("shado.xpm");
	beta->textur_path[2] = strdup("test.xpm");
	beta->textur_path[3] = strdup("wall1.xpm");
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

int	color(int y, int i)
{
	int color;
	
	if (worldMap[y][i] == 1)
		color = 0x00a86b;
	else if (worldMap[y][i] == 2)
		color = 0xfff000;
	else if (worldMap[y][i] == 3)
		color = 0x0000ff;
	else
		color = 0x000000;
	return (color);
}

void	draw_line(t_beta *beta, int i, int y, int x)
{
	t_dda dda;

	dda.color = color(y, i);
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
			if (worldMap[y][i] == 5)
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
		x = screenWidth/2;
		if (y < screenHeight/2)
			color = 0x3881CA;
		else
			color = 0x275B2A;
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
	if(keycode == 126)
	{
		x = (int)(((beta->player_x * B + beta->shift_x - beta->pdx*15)/B));
		y = (int)(((beta->player_y * B + beta->shift_y - beta->pdy*15) / B));
		x1 = (int)(((beta->player_x * B + beta->shift_x - beta->pdx*20)/B));
		y1 = (int)(((beta->player_y * B + beta->shift_y - beta->pdy) / B));
		
	}
	else if (keycode == 125)
	{
		x = (int)(((beta->player_x * B + beta->shift_x + beta->pdx*15)/B));
		y = (int)(((beta->player_y * B + beta->shift_y + beta->pdy*15) / B));
		x1 = (int)(((beta->player_x * B + beta->shift_x + beta->pdx*20)/B));
		y1 = (int)(((beta->player_y * B + beta->shift_y + beta->pdy) / B));
	}


	if (worldMap[y][x] != 1 && worldMap[y1][x1] != 1)
		return(0);
	
	return(-1);
}


int	key_hook(int keycode, t_beta *beta)
{
	int b = 0;

		if (keycode == 126  && check_wall(beta, keycode) == 0 )
		{

			beta->shift_y -= beta->pdy * 5;
			beta->shift_x -= beta->pdx * 5;
		}
		 if (keycode == 125 && check_wall(beta, keycode) == 0)
		{
			beta->shift_y += beta->pdy* 5;
			beta->shift_x += beta->pdx*5;

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
		bzero(beta->image3D.addr, sizeof(int)*(screenWidth / 2) * screenHeight );
		backgrand(beta);
		randring(beta);
		mlx_put_image_to_window(beta->mlx, beta->win, beta->image.img, 0, 0);
		mlx_put_image_to_window(beta->mlx, beta->win, beta->image3D.img, screenWidth / 2, 0);
	return(0);
}






void	ft_init(t_beta *beta, char *arg)
{
	// parse_map(beta, arg);
	beta->_const = 70 * 0.0174532925;
	beta->pdx = cos(beta->_const);
	beta->pdy = sin(beta->_const);
	beta->i = 00, beta->y = 0, beta->shift_x = 0, beta->shift_y = 0;
	beta->mlx = mlx_init();
	beta->win = mlx_new_window(beta->mlx, screenWidth, screenHeight, "CUB3D");
	beta->image.img = mlx_new_image(beta->mlx, screenWidth, screenHeight);
	beta->image.addr = mlx_get_data_addr(beta->image.img, &beta->image.bits_per_pixel, &beta->image.line_length, &beta->image.endian);
	beta->image3D.img = mlx_new_image(beta->mlx, screenWidth / 2, screenHeight);
	beta->image3D.addr = mlx_get_data_addr(beta->image3D.img, &beta->image3D.bits_per_pixel, &beta->image3D.line_length, &beta->image3D.endian);
	ft_textur(beta);
	backgrand(beta);
	beta->map = calloc(sizeof(t_map), 1);
	beta->map->width = 17;
	beta->map->height = 14;
	randring(beta);
	mlx_put_image_to_window(beta->mlx, beta->win, beta->image.img, 0, 0);
	mlx_put_image_to_window(beta->mlx, beta->win, beta->image3D.img, screenWidth / 2, 0);
	mlx_key_hook(beta->win, key_hook, beta);
	mlx_hook(beta->win, 2, 0, key_hook, beta);
	mlx_loop(beta->mlx);
}

int main()
{
	t_beta *beta;

	beta = calloc(sizeof(t_beta), 1);
	ft_init(beta, "NULL");
}