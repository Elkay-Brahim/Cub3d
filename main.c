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

#include <string.h>


#define PI 3.14159265359
#define mapWidth 24
#define mapHeight 24
#define screenHeight 560
#define screenWidth 1360
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

	float pos_px;
	float pos_py;
	float __des;
	float intersect_x;
	float intersect_y;

	float rx;
	float ry;

	float pdy;
	float _const;
}		t_beta;

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
  {1,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,5,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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


void drw_line(t_beta *beta)
{

	int it = 1;
	int inter = 100;
	int u = 0;
		float teta = 0 ;
		float dx;
		float dy;
		float des;
		float point_Y = 0;
		float point_X = 0;
		float des_x;
		float des_y;
		float angle;
	dy = 0;
	dx = 0;


		float new_des_x;
		float new_des_y;
	float save = beta->_const;
	float _save = beta->pdx;
	float __save = beta->pdy;
	float __angle_start = beta->_const - 0.523598776;
	float __angle_end = beta->_const + 0.523598776;
		int __j = 1;
	beta->pos_px = (beta->p_x*B+beta->shfit_x);
	beta->pos_py = (beta->p_y*B+beta->shfit_y);
	if (beta->_const-0.523598776 <= 0)
	{
		__angle_start = beta->_const + 5.75958653;
		__angle_end = beta->_const + 6.28318531 + 0.523598776;
	}
	beta->_const = __angle_start;

	while (beta->_const <= __angle_end)
	{
		__j = 1;


		 if (beta->_const <= save)
		 {
			beta->_const += 0.005;
			if(beta->_const > 2 * PI)
				beta->_const -= 2 * PI;
			beta->pdx = cos(beta->_const  ) ;
			beta->pdy = sin(beta->_const) ;
		 }
		 else
		 {
			beta->_const += 0.005;
			if (beta->_const < 0)
				beta->_const += 2 * PI;
			beta->pdx = cos(beta->_const ) ;
			beta->pdy = sin(beta->_const ) ;
		 }
		while(1)
		{
		// calcul destance
			if ((beta->_const * 180)/PI > 90 && (beta->_const * 180)/PI < 270)
			{
				dx = (beta->p_x * B  + beta->shfit_x) - (int)(((beta->p_x * B  + beta->shfit_x) / B) + __j ) * B;
				new_des_x = (dx / cos(beta->_const)) + 1 ;
			}
			else
			{
				dx = (beta->p_x * B  + beta->shfit_x) - (int)(((beta->p_x * B  + beta->shfit_x) / B) + 1 - __j) * B;
				new_des_x = (dx / cos(beta->_const)) + 1 ;
			}




			float angle_A;
		

				angle_A = beta->_const;

			if ((int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_x)/B) <= 0 || (int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_x)/B) > 13)
				break;
			if ((int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_x)/B) <= 0 || (int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_x)/B) > 16)
				break;

			
			if ( worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_x)/B)][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_x)/B)] == 1)
				break;
			if ( worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_x)/B)][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_x)/B)] == 0 )
			{
				if (((beta->_const * 180)/PI  > 0 && (beta->_const * 180)/PI  < 90 )|| (beta->_const * 180)/PI  > 360)
				{
					if ( worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_x)/B)+1][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_x)/B)] == 1  && worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_x)/B)][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_x)/B)+1] == 1)
						break;
				}
				else if ((beta->_const * 180)/PI  > 90 && (beta->_const * 180)/PI  < 180)
				{
					if ( worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_x)/B)+1][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_x)/B)] == 1  && worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_x)/B)][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_x)/B)-1] == 1)
						break;
				}
				else if ((beta->_const * 180)/PI  > 180 && (beta->_const * 180)/PI  < 270)
				{
					if ( worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_x)/B)-1][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_x)/B)] == 1  && worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_x)/B)][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_x)/B)-1] == 1)
						break;
				}
				else if ((beta->_const * 180)/PI  > 270 && (beta->_const * 180)/PI  < 360)
				{
					if ( worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_x)/B)+1][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_x)/B)] == 1  && worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_x)/B)][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_x)/B)+1] == 1)
						break;
				}
			}


			__j++;
		}
		__j=1;
		while(1)
		{

			if (((beta->_const * 180)/PI) > 180 && ((beta->_const * 180)/PI) < 360)
			{
				dy = (beta->p_y * B  + beta->shfit_y) - (int)(((beta->p_y * B  + beta->shfit_y) / B) + __j ) * B;
				new_des_y = (dy / sin(beta->_const))  + 1;

			}
			else
			{
				dy = (beta->p_y * B  + beta->shfit_y) - (int)(((beta->p_y * B  + beta->shfit_y) / B) + 1 - __j)  * B;
				new_des_y = (dy / sin(beta->_const)) + 1;
			}
			
			if ((int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_y)/B) <= 0 || (int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_y)/B) > 13)
				break;
			if ((int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_y)/B) <= 0 || (int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_y)/B) > 16)
				break;

			if ( worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_y)/B)][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_y)/B)] == 1 )
				break;
			if ( worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_y)/B)][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_y)/B)] == 0 )
			{
				if ((beta->_const * 180)/PI  > 0 && (beta->_const * 180)/PI  < 90)
				{
					if ( worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_y)/B)+1][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_y)/B)] == 1  && worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_y)/B)][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_y)/B)+1] == 1)
						break;
				}
				else if ((beta->_const * 180)/PI  > 90 && (beta->_const * 180)/PI  < 180)
				{
					if ( worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_y)/B)+1][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_y)/B)] == 1  && worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_y)/B)][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_y)/B)-1] == 1)
						break;
				}
				else if ((beta->_const * 180)/PI  > 180 && (beta->_const * 180)/PI  < 270)
				{
					if ( worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_y)/B)-1][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_y)/B)] == 1  && worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_y)/B)][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_y)/B)-1] == 1)
						break;
				}
				else if ((beta->_const * 180)/PI  > 270 && (beta->_const * 180)/PI  < 360)
				{
					if ( worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_y)/B)-1][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_y)/B)] == 1  && worldMap[(int)((beta->p_y*B+beta->shfit_y - beta->pdy * new_des_y)/B)][(int)((beta->p_x*B+beta->shfit_x - beta->pdx * new_des_y)/B)+1] == 1)
						break;
				}
			}

			__j++;

		}



		// float __x;
		if (fabs(new_des_x) <= fabs(new_des_y))
			beta->__des = fabs(new_des_x);
		else
			beta->__des = fabs(new_des_y);
		beta->intersect_x = ((beta->p_x*B+beta->shfit_x + beta->pdx * beta->__des ));
		beta->intersect_y = ((beta->p_y*B+beta->shfit_y + beta->pdy * beta->__des));

			float tmp_x, tmp_y;
			float destance_x =  beta->pos_px - beta->intersect_x;
			float destance_y =  beta->pos_py - beta->intersect_y;
			float step = fmax(fabs(destance_x), fabs(destance_y));
			destance_x = (destance_x) / step;
			destance_y = (destance_y) / step;
			float x = ((destance_x));
			float y = (destance_y );
			float t_x = tmp_x;
			float t_y = tmp_y;
			float tfo_x;
			float tfo_y;
			tmp_x = beta->p_x*B+beta->shfit_x;
			tmp_y = beta->p_y*B+beta->shfit_y;
			float cast_x;
		
			while(it <= step)
			{

				tmp_x += destance_x;
				tmp_y += destance_y;
				my_mlx_pixel_put(&beta->image, (tmp_x) , (tmp_y) , 0xE50000);


				it++;
			}
			it = 1;
	
	}
	beta->_const = save;
	beta->pdy = __save;
	beta->pdx = _save;
}


void randring(t_beta *beta)
{
	while(beta->y < 14)
	{
		beta->i = 0;
		while(beta->i < 17)
		{
			float x = 0;
			while(x <= B)
			{
				int color;
				float tmp_x1, tmp_y1;
				float destance_x1 = (float) (beta->i*B+x - (beta->i)*B);
				float destance_y1 = (float) (beta->y*B - (beta->y+1)*B);
				float step1 = fmax(fabs(destance_x1), fabs(destance_y1));
				destance_x1 = fabs(destance_x1) / step1;
				destance_y1 = fabs(destance_y1) / step1;
				int it1 = 1;
				tmp_x1 = beta->i*B;
				tmp_y1 = beta->y*B;
				while(it1 <= step1)
				{
					if(worldMap[beta->y][beta->i] == 1)
						my_mlx_pixel_put(&beta->image, tmp_x1 , tmp_y1 , 0x00a86b);
					else
						my_mlx_pixel_put(&beta->image, tmp_x1 , tmp_y1 , 0xe3e1e6);
					tmp_x1 += destance_x1;
					tmp_y1 += destance_y1;
					it1++;
				}

				float tmp_x, tmp_y;
				float destance_x = (float) (beta->i*B - (beta->i+1)*B);
				float destance_y = (float) (beta->y*B+x - (beta->y)*B);
				float step = fmax(fabs(destance_x), fabs(destance_y));
				destance_x = fabs(destance_x) / step;
				destance_y = fabs(destance_y) / step;
				int it = 1;
				tmp_x = beta->i*B;
				tmp_y = beta->y*B;
				while(it <= step)
				{
					if(worldMap[beta->y][beta->i] == 1)
						my_mlx_pixel_put(&beta->image, tmp_x , tmp_y , 0x00a86b);
					else
						my_mlx_pixel_put(&beta->image, tmp_x , tmp_y , 0xe3e1e6);
					tmp_x += destance_x;
					tmp_y += destance_y;
					it++;
				}
				x++;
			}



				float tmp_x1, tmp_y1;
				float destance_x1 = (float) (beta->i*B - (beta->i)*B);
				float destance_y1 = (float) (beta->y*B - (beta->y+1)*B);
				float step1 = fmax(fabs(destance_x1), fabs(destance_y1));
				destance_x1 = fabs(destance_x1) / step1;
				destance_y1 = fabs(destance_y1) / step1;
				int it1 = 1;
				tmp_x1 = beta->i*B;
				tmp_y1 = beta->y*B;
				while(it1 <= step1)
				{
					my_mlx_pixel_put(&beta->image, tmp_x1 , tmp_y1 , 0x000000);
					tmp_x1 += destance_x1;
					tmp_y1 += destance_y1;
					it1++;
				}

				float tmp_x, tmp_y;
				float destance_x = (float) (beta->i*B - (beta->i+1)*B);
				float destance_y = (float) (beta->y*B - (beta->y)*B);
				float step = fmax(fabs(destance_x), fabs(destance_y));
				destance_x = fabs(destance_x) / step;
				destance_y = fabs(destance_y) / step;
				int it = 1;
				tmp_x = beta->i*B;
				tmp_y = beta->y*B;
				while(it <= step)
				{
					my_mlx_pixel_put(&beta->image, tmp_x , tmp_y , 0x000000);

					tmp_x += destance_x;
					tmp_y += destance_y;
					it++;
				}


				if (worldMap[beta->y][beta->i] == 5)
				{
					beta->p_x = beta->i;
					beta->p_y = beta->y;
				}
			beta->i++;
		}
		beta->y++;
	}
		int b = 0;
		while(b < 10)
		{
			my_mlx_pixel_put(&beta->image, (((beta->p_x*B)+b)+ beta->shfit_x)-5 , (((beta->p_y*B))+ beta->shfit_y)-5 , 0xff0000);
			my_mlx_pixel_put(&beta->image, (((beta->p_x*B))+ beta->shfit_x)-5 , (((beta->p_y*B)+b)+ beta->shfit_y)-5 , 0xff0000);
			my_mlx_pixel_put(&beta->image, ((((beta->p_x*B)+10)-b)+ beta->shfit_x )-5, (((beta->p_y*B)+10)+ beta->shfit_y)-5 , 0xff0000);
			my_mlx_pixel_put(&beta->image, (((beta->p_x*B)+10)+ beta->shfit_x)-5 , ((((beta->p_y*B)+10)-b)+ beta->shfit_y)-5 , 0xff0000);
			b++;
		}
		drw_line(beta);

	beta->i = 0;
	beta->y = 0;
}



int	key_hook(int keycode, t_beta *beta)
{
	int b = 0;
	if (worldMap[(int)(((beta->p_y*B+beta->shfit_y - beta->pdy*10)/B))][(int)(((beta->p_x*B+beta->shfit_x - beta->pdx*10)/B))] != 1)
	{

		if (keycode == 126)
		{
			beta->shfit_y -= beta->pdy*5;
			beta->shfit_x -= beta->pdx*5;
		}
	}
	if (worldMap[(int)(((beta->p_y*B+beta->shfit_y + beta->pdy*10)/B))][(int)(((beta->p_x*B+beta->shfit_x + beta->pdx *10)/B))] != 1)
	{
		 if (keycode == 125)
		{
			beta->shfit_y += beta->pdy* 5;
			beta->shfit_x += beta->pdx*5;

		}
	}
	 if (keycode == 124)
		{
			beta->_const += 0.1;
			if(beta->_const > 2 * PI)
				beta->_const -= 2 * PI;
			beta->pdx = cos(beta->_const) ;
			beta->pdy = sin(beta->_const) ;
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
		randring(beta);
		mlx_put_image_to_window(beta->mlx, beta->win, beta->image.img, 0, 0);
	return(0);
}

int main()
{
	t_beta beta;
	beta._const = 30 * 0.0174532925;
	beta.pdx = cos(beta._const);
	beta.pdy = sin(beta._const);
	beta.i = 00, beta.y = 0, beta.shfit_x = 0, beta.shfit_y = 0;
	beta.mlx = mlx_init();
	beta.win = mlx_new_window(beta.mlx, screenWidth, screenHeight, "CUB3D");
	beta.image.img = mlx_new_image(beta.mlx, screenWidth, screenHeight);
	beta.image.addr = mlx_get_data_addr(beta.image.img, &beta.image.bits_per_pixel, &beta.image.line_length, &beta.image.endian);

	randring(&beta);
	mlx_put_image_to_window(beta.mlx, beta.win, beta.image.img, 0, 0);
	mlx_key_hook(beta.win, key_hook, &beta);
	mlx_hook(beta.win, 2, 0, key_hook, &beta);
	mlx_loop(beta.mlx);
}