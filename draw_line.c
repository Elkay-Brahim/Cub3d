/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:51:16 by rrasezin          #+#    #+#             */
/*   Updated: 2023/08/02 20:19:12 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_cord
{
    float x;
    float y;
    int color;
}              t_cord;

typedef struct s_dda_
{
    float   dx;
    float   dy;
    float   max;
    float   step_x;
    float   step_y;
    float   new_x;
    float   new_y;
}              t_dda_;

void    draw_____line(t_beta *beta, t_cord p1, t_cord p2)
{
    t_dda_   line;
    int i;
    i = 1;
    line.dx = p1.x - p2.x;
    line.dy = p1.y - p2.y;
    line.max = fmax(fabs(line.dx), fabs(line.dy));
    line.step_x = fabs(line.dx) / line.max;
    line.step_y = fabs(line.dy) / line.max;
    line.new_x = p1.x;
    line.new_y = p1.y;
    int text_x;
    int text_y = 0;

    // printf("textur %d\n", beta->textur_i);
    if (beta->inter_wall_side == WALL_SIDE_Y)
    {
        
        text_x = (beta->textur[beta->textur_i].width / B ) * (beta->intersect_x - ((int)(beta->intersect_x / B ) * B));
    }
    else
    {
        text_x = (beta->textur[beta->textur_i].width / B ) * (beta->intersect_y - ((int)(beta->intersect_y / B ) * B));
        
    }
    // printf("line max %f | dx:%f | dy:%f \n", line.max, line.dx, line.dy);
    // pause();
    while (i < line.max)
    {
        text_y = fabs((beta->textur[beta->textur_i].height - 1) - ((beta->textur[beta->textur_i].height*(fabs(p2.y - line.new_y))) /line.max));
        if (line.new_y >= 0 && line.new_y < screenHeight && line.new_x < screenWidth )
            my_mlx_pixel_put(&beta->image3D, line.new_x, line.new_y, beta->textur[beta->textur_i].map[text_y][text_x]);
        // printf ("text_y :%d, text_x: %d color: %d\n", text_y,text_x, beta->map_color[text_y][text_x]);
        line.new_x += line.step_x;
        line.new_y += line.step_y;
        i++;
        // text_y++;
    }
    return ;
}

void    draw_wall(t_beta *beta)
{
    t_cord p1;
    t_cord p2;

    float middel;
    int i = 0;
    float ca;

    ca = beta->_const - beta->__angle_start;
    printf("---------- %f\n", (beta->__angle_start * 180)/PI);

    if (ca < 0)
        ca += 2*PI;
    if (ca > 2*PI)
        ca -= 2*PI;
    beta->__des = (beta->__des * cos(ca));
    p1.x = beta->wall_x;
    p2.x = beta->wall_x;

    // if (beta->__des < 1)
    // {
    //     if (beta->__des < 0)
    //         beta->__des = beta->__des * -1;
    //     else
    //        beta->__des = 1; 
    // }
    // else
        p2.y = ((B * WALL) / beta->__des);
		 printf("distance :%f\n", p2.y);
    
   
    middel = p2.y / 2;
    p1.y = (screenHeight / 2) - middel;
    p2.y = screenHeight / 2 + middel;

     draw_____line(beta, p1, p2);

}