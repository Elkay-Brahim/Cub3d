/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by bchifour          #+#    #+#             */
/*   Updated: 2023/07/17 19:B:46 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>



#define mapWidth 24
#define mapHeight 24
#define screenWidth 1500
#define screenHeight 1500
#define B 40

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};



void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}



static void	line_d(t_data mlx, int y, int x , int x1, int y1)
{
	// t_line	l;
	// int		color;

	// l.dx = (float)(map[y][x + 1].x - map[y][x].x);
	// l.dy = (float)(map[y][x + 1].y - map[y][x].y);
	// l.step = fmax(fabs(l.dx), fabs(l.dy));
	// l.dx = l.dx / l.step;
	// l.dy = l.dy / l.step;
	// l.x = map[y][x].x;
	// l.y = map[y][x].y;
	// l.i = 1;
	// while (l.i <= l.step)
	// {
	// 	my_mlx_pixel_put(&mlx->i, l.x + mlx->m.m_left, l.y + mlx->m.m_up, color);
	// 	l.x += l.dx;
	// 	l.y += l.dy;
	// 	l.i++;
	// }


	//-----------------------------------------------------------------

	float tmp_x, tmp_y;
	float destance_x = (float) (x - x1);
	float destance_y = (float) (y - y1);
	float step = fmax(fabs(destance_x), fabs(destance_y));
	destance_x = destance_x / step;
	destance_y = destance_y / step;
	int i = 1;
	tmp_x = x;
	tmp_y = y;
	// printf("---------- %f\n", step);
	while(i <= step)
	{
		
		my_mlx_pixel_put(&mlx, tmp_x , tmp_y , 0xffffff);
		tmp_x += destance_x;
		tmp_y += destance_y;
		// printf("HI");
		i++;
	}
	
}

int main()
{
	t_data image;
	int i = 00, y = 0;
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, screenWidth, screenHeight, "CUB3D");
	image.img = mlx_new_image(mlx, screenWidth, screenHeight);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
	while(y < 14)
	{
		i = 0;
		while(i < 17)
		{
			float x = 0;
			while(x <= B)
			{
				int color;
				float tmp_x1, tmp_y1;
				float destance_x1 = (float) (i*B+x - (i)*B);
				float destance_y1 = (float) (y*B - (y+1)*B);
				float step1 = fmax(fabs(destance_x1), fabs(destance_y1));
				destance_x1 = fabs(destance_x1) / step1;
				destance_y1 = fabs(destance_y1) / step1;
				int it1 = 1;
				tmp_x1 = i*B;
				tmp_y1 = y*B;
				while(it1 <= step1)
				{
					// printf("%f  %f \n", tmp_x1, tmp_y1);
					if(worldMap[y][i] == 1)
					{
						
						my_mlx_pixel_put(&image, tmp_x1 , tmp_y1 , 0x00a86b);
						// my_mlx_pixel_put(&image, tmp_y1-B , tmp_x1 , 0xE73fff);
					}
					else
						my_mlx_pixel_put(&image, tmp_x1 , tmp_y1 , 0xe3e1e6);
					if ( x == 1)
						my_mlx_pixel_put(&image, tmp_x1 , tmp_y1 , 0x000000);
					tmp_x1 += destance_x1;
					tmp_y1 += destance_y1;
					it1++;
				}

				float tmp_x, tmp_y;
				float destance_x = (float) (i*B - (i+1)*B);
				float destance_y = (float) (y*B+x - (y)*B);
				float step = fmax(fabs(destance_x), fabs(destance_y));
				destance_x = fabs(destance_x) / step;
				destance_y = fabs(destance_y) / step;
				int it = 1;
				tmp_x = i*B;
				tmp_y = y*B;
				while(it <= step)
				{
					if(worldMap[y][i] == 1)
					{
						
						// my_mlx_pixel_put(&image, tmp_y-B , tmp_x , 0xE73fff);
						my_mlx_pixel_put(&image, tmp_x , tmp_y , 0x00a86b);
					}
					else
						my_mlx_pixel_put(&image, tmp_x , tmp_y , 0xe3e1e6);

					if (x == 1)
						my_mlx_pixel_put(&image, tmp_x , tmp_y , 0x000000);

					tmp_x += destance_x;
					tmp_y += destance_y;
					it++;
				}
				x++;
			}
				if (worldMap[y][i] == 5)
				{
					int b = 0;
					while(b < 10)
					{
						my_mlx_pixel_put(&image, ((i*B)+b)- 5 , ((y*B))- 5 , 0xff0000);
						my_mlx_pixel_put(&image, ((i*B))- 5 , ((y*B)+b)- 5 , 0xff0000);
						my_mlx_pixel_put(&image, (((i*B)+10)-b)- 5 , ((y*B)+10)- 5 , 0xff0000);
						my_mlx_pixel_put(&image, ((i*B)+10)- 5 , (((y*B)+10)-b)- 5 , 0xff0000);
						b++;
					}
				}
			i++;
		}
		y++;
	}
	
	mlx_put_image_to_window(mlx, win, image.img, 0, 0);
	mlx_loop(mlx);
}