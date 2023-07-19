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
#include <unistd.h>


#define PI 3.14159265359
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

	float rx;
	float ry;

	float pdy;
	float _const;
}		t_beta;

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

void drw_ray(t_beta beta)
{
	int r, mx, my, mp, dof;
	float rx , ry, ra, xo, yo;
	ra = beta._const;
	r = 0;
	while(r < 1)
	{
		dof = 0;
		float atan = -1/tan(ra);
		if(ra > PI)
		{
			ry = (((int)beta.y >> 6) << 6) - 0.0001;
			rx = (beta.y - ry) * atan + beta.i;
			yo = -64;
			xo = -yo * atan;
		}
		if(ra < PI)
		{
			ry = (((int)beta.y >> 6) << 6) +64;
			rx = (beta.y - ry) * atan + beta.i;
			yo = 64;
			xo = -yo * atan;
		}
		if(ra == 0 || ra == PI)
		{
			rx = beta.i;
			ry = beta.y;
			dof = 8;
		}
		while(dof < 8)
		{
			mx = (int) (rx) >> 6;
			my = (int) (ry) >> 6;
			mp = my * 14 + mx;
			printf("%d\n", mp);
			if (mp > 0 &&  mp < 17 * 14 && worldMap[beta.y][mp] == 1)
				dof = 8;
			else
			{
				rx+=xo;
				ry+=yo;
				dof+=1;
			}
		}
		r++;
	}
	float tmp_x, tmp_y;
	float destance_x = (float) ((beta.i*B+beta.shfit_x) - (beta.i*B+beta.shfit_x + rx));
	float destance_y = (float) ((beta.y*B+beta.shfit_y )- (beta.y*B+beta.shfit_y + ry));
	float step = fmax(fabs(destance_x), fabs(destance_y));
	destance_x = (destance_x) / step;
	destance_y = (destance_y) / step;
	int it = 1;
	tmp_x = beta.i*B+beta.shfit_x;
	tmp_y = beta.y*B+beta.shfit_y;
	while(it <= step)
	{
		my_mlx_pixel_put(&beta.image, tmp_x , tmp_y , 0xe50000);
		tmp_x += destance_x;
		tmp_y += destance_y;
		it++;
	}
}

void drw_line(t_beta beta)
{
	float tmp_x, tmp_y;
	float destance_x = (float) ((beta.i*B+beta.shfit_x) - (beta.i*B+beta.shfit_x + beta.pdx * 5));
	float destance_y = (float) ((beta.y*B+beta.shfit_y )- (beta.y*B+beta.shfit_y + beta.pdy * 5));
	float step = fmax(fabs(destance_x), fabs(destance_y));
	destance_x = (destance_x) / step;
	destance_y = (destance_y) / step;
	int it = 1;
	tmp_x = beta.i*B+beta.shfit_x;
	tmp_y = beta.y*B+beta.shfit_y;
	while(it <= step)
	{
		my_mlx_pixel_put(&beta.image, tmp_x , tmp_y , 0x000000);
		tmp_x += destance_x;
		tmp_y += destance_y;
		it++;
	}
}


void randring(t_beta beta)
{





	while(beta.y < 14)
	{
		beta.i = 0;
		while(beta.i < 17)
		{
			float x = 0;
			while(x <= B)
			{
				int color;
				float tmp_x1, tmp_y1;
				float destance_x1 = (float) (beta.i*B+x - (beta.i)*B);
				float destance_y1 = (float) (beta.y*B - (beta.y+1)*B);
				float step1 = fmax(fabs(destance_x1), fabs(destance_y1));
				destance_x1 = fabs(destance_x1) / step1;
				destance_y1 = fabs(destance_y1) / step1;
				int it1 = 1;
				tmp_x1 = beta.i*B;
				tmp_y1 = beta.y*B;
				while(it1 <= step1)
				{
					// printf("%f  %f \n", tmp_x1, tmp_y1);
					if(worldMap[beta.y][beta.i] == 1)
					{
						
						my_mlx_pixel_put(&beta.image, tmp_x1 , tmp_y1 , 0x00a86b);
						// my_mlx_pixel_put(&image, tmp_y1-B , tmp_x1 , 0xE73fff);
					}
					else
						my_mlx_pixel_put(&beta.image, tmp_x1 , tmp_y1 , 0xe3e1e6);
					tmp_x1 += destance_x1;
					tmp_y1 += destance_y1;
					it1++;
				}

				float tmp_x, tmp_y;
				float destance_x = (float) (beta.i*B - (beta.i+1)*B);
				float destance_y = (float) (beta.y*B+x - (beta.y)*B);
				float step = fmax(fabs(destance_x), fabs(destance_y));
				destance_x = fabs(destance_x) / step;
				destance_y = fabs(destance_y) / step;
				int it = 1;
				tmp_x = beta.i*B;
				tmp_y = beta.y*B;
				while(it <= step)
				{
					if(worldMap[beta.y][beta.i] == 1)
					{
						
						// my_mlx_pixel_put(&image, tmp_y-B , tmp_x , 0xE73fff);
						my_mlx_pixel_put(&beta.image, tmp_x , tmp_y , 0x00a86b);
					}
					else
						my_mlx_pixel_put(&beta.image, tmp_x , tmp_y , 0xe3e1e6);

					tmp_x += destance_x;
					tmp_y += destance_y;
					it++;
				}
				x++;
			}



				float tmp_x1, tmp_y1;
				float destance_x1 = (float) (beta.i*B - (beta.i)*B);
				float destance_y1 = (float) (beta.y*B - (beta.y+1)*B);
				float step1 = fmax(fabs(destance_x1), fabs(destance_y1));
				destance_x1 = fabs(destance_x1) / step1;
				destance_y1 = fabs(destance_y1) / step1;
				int it1 = 1;
				tmp_x1 = beta.i*B;
				tmp_y1 = beta.y*B;
				while(it1 <= step1)
				{
					my_mlx_pixel_put(&beta.image, tmp_x1 , tmp_y1 , 0x000000);
					tmp_x1 += destance_x1;
					tmp_y1 += destance_y1;
					it1++;
				}

				float tmp_x, tmp_y;
				float destance_x = (float) (beta.i*B - (beta.i+1)*B);
				float destance_y = (float) (beta.y*B - (beta.y)*B);
				float step = fmax(fabs(destance_x), fabs(destance_y));
				destance_x = fabs(destance_x) / step;
				destance_y = fabs(destance_y) / step;
				int it = 1;
				tmp_x = beta.i*B;
				tmp_y = beta.y*B;
				while(it <= step)
				{
					my_mlx_pixel_put(&beta.image, tmp_x , tmp_y , 0x000000);

					tmp_x += destance_x;
					tmp_y += destance_y;
					it++;
				}


				if (worldMap[beta.y][beta.i] == 5)
				{
					beta.p_x = beta.i;
					beta.p_y = beta.y;
					int b = 0;
					while(b < 10)
					{
						my_mlx_pixel_put(&beta.image, ((beta.p_x*B)+b)+ beta.shfit_x , ((beta.p_y*B))+ beta.shfit_y , 0xff0000);
						my_mlx_pixel_put(&beta.image, ((beta.p_x*B))+ beta.shfit_x , ((beta.p_y*B)+b)+ beta.shfit_y , 0xff0000);
						my_mlx_pixel_put(&beta.image, (((beta.p_x*B)+10)-b)+ beta.shfit_x , ((beta.p_y*B)+10)+ beta.shfit_y , 0xff0000);
						my_mlx_pixel_put(&beta.image, ((beta.p_x*B)+10)+ beta.shfit_x , (((beta.p_y*B)+10)-b)+ beta.shfit_y , 0xff0000);
						b++;
					}
					drw_line(beta);
					// drw_ray(beta);
				}
			beta.i++;
		}
		beta.y++;
	}
}



int	key_hook(int keycode, t_beta *beta)
{
	int b = 0;
	printf("%d\n", keycode);
	if (keycode == 126)
	{
		beta->shfit_y -= beta->pdy;
		beta->shfit_x -= beta->pdx;

	}
	else if (keycode == 125)
	{
		beta->shfit_y += beta->pdy;
		beta->shfit_x += beta->pdx;

	}
	else if (keycode == 124)
	{
		beta->_const += 0.1;
		if(beta->_const > 2 * PI)
			beta->_const -= 2 * PI;
		beta->pdx = cos(beta->_const) * 5;
		beta->pdy = sin(beta->_const) * 5;
	}
	else if (keycode == 123)
	{
		beta->_const -= 0.1;
		if (beta->_const < 0)
			beta->_const += 2 * PI;
		beta->pdx = cos(beta->_const) * 5;
		beta->pdy = sin(beta->_const) * 5;

	}

	mlx_clear_window(beta->mlx, beta->win);
	randring(*beta);
	mlx_put_image_to_window(beta->mlx, beta->win, beta->image.img, 0, 0);
	return(0);
}

int main()
{
	t_beta beta;
	beta.pdx = cos(beta._const) * 5;
	beta.pdy = sin(beta._const) * 5;
	beta.i = 00, beta.y = 0, beta.shfit_x = 5, beta.shfit_y = 5;
	beta.mlx = mlx_init();
	beta.win = mlx_new_window(beta.mlx, screenWidth, screenHeight, "CUB3D");
	beta.image.img = mlx_new_image(beta.mlx, screenWidth, screenHeight);
	beta.image.addr = mlx_get_data_addr(beta.image.img, &beta.image.bits_per_pixel, &beta.image.line_length, &beta.image.endian);

	randring(beta);
	mlx_put_image_to_window(beta.mlx, beta.win, beta.image.img, 0, 0);
	mlx_key_hook(beta.win, key_hook, &beta);
	mlx_hook(beta.win, 2, 0, key_hook, &beta);
	// mlx_hook(vars.win, 17, 0, cross_window, &vars);
	mlx_loop(beta.mlx);
}