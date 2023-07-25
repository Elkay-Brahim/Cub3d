/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:51:16 by rrasezin          #+#    #+#             */
/*   Updated: 2023/07/25 15:13:48 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

typedef struct s_cord
{
    float x;
    float y;
    int color;
}              t_cord;

typedef struct s_dda
{
    float   dx;
    float   dy;
    float   max;
    float   step_x;
    float   step_y;
    float   new_x;
    float   new_y;
}              t_dda;

void    draw_____line(t_beta *beta, t_cord p1, t_cord p2)
{
    t_dda   line;
    int i;
    i = 0;
    line.dx = p1.x - p2.x;
    line.dy = p1.y - p2.y;
    line.max = fmax(fabs(line.dx), fabs(line.dy));
    line.step_x = fabs(line.dx) / line.max;
    line.step_y = fabs(line.dy) / line.max;
    line.new_x = p1.x;
    line.new_y = p1.y;
    while (i < line.max)
    {
        // printf ("ok\n");
        my_mlx_pixel_put(&beta->image3D, line.new_x, line.new_y, p1.color);
        line.new_x += line.step_x;
        line.new_y += line.step_y;
        i++;
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
    
    ca = beta->save - beta->_const;
    if (ca < 0)
        ca += 2*PI;
    if (ca > 2*PI)
        ca -= 2*PI;
    beta->__des = beta->__des * cos(ca);
    p1.x = beta->wall_x;
    p1.y = 0;
    p1.color = beta->color;
    
    p2.x = beta->wall_x;
    
    p2.y = ((B * WALL) / beta->__des) * 1.5;
    if (p2.y > WALL)
        p2.y = WALL;
    middel = p2.y / 2;
    p1.y = (screenHeight / 2) - middel;
    p2.y = screenHeight / 2 + middel;
    int const_1 = p1.x + 4;
    while (p1.x < const_1)
    {
    // printf ("%f  %f\n", p1.y , p2.y);
        draw_____line(beta, p1, p2);
        p1.x++;
        p2.x++;
        i++;
        if (p1.x > screenWidth/2)
            break;
    }
}