/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:51:16 by rrasezin          #+#    #+#             */
/*   Updated: 2023/07/27 18:54:30 by bchifour         ###   ########.fr       */
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

void    draw_____line(t_beta *beta, t_cord p1, t_cord p2, int st)
{
    t_dda   line;
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

    // if (beta->inter_wall_side == WALL_SIDE_X)
    //     return;
    // if (beta->inter_wall_side != WALL_SIDE_X)
        // text_x =((beta->textur_width * line.new_x)/ line.max);
        // text_x = ( 1.0 - p1.x / line.max) * beta->textur_width;
    if (beta->inter_wall_side == WALL_SIDE_Y)
        text_x = (beta->textur_width / B ) * (beta->intersect_x - (int)(beta->intersect_x / B ) * B);
    else
        text_x = (beta->textur_width / B ) * (beta->intersect_y - (int)(beta->intersect_y / B ) * B);
        
    

        // printf("------- %d\n", text_x);
    while (i < line.max)
    {
        // if (beta->inter_wall_side != WALL_SIDE_X)
        //     text_y =((beta->textur_height * (i))/ (line.max+100));
        // else
        // {
        //     text_y = ((beta->textur_height * i)/ line.max);
        // }
        text_y = (beta->textur_height - 1) - ((beta->textur_height*(fabs(p2.y - line.new_y))) /line.max);
        if (line.new_y >= 0 && line.new_y < screenHeight && line.new_x < screenWidth && line.new_x > 0)
            my_mlx_pixel_put(&beta->image3D, line.new_x, line.new_y, beta->map_color[text_y][text_x]);
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

    static int st;
    
    if (st >= beta->textur_width-1)
        st = 0;
    ca = beta->save - beta->_const;
    if (ca < 0)
        ca += 2*PI;
    if (ca > 2*PI)
        ca -= 2*PI;
    beta->__des = beta->__des * cos(ca);
    
    p1.x = beta->wall_x;
    p1.y = 0;
    
    p2.x = beta->wall_x;
    
    p2.y = ((B * WALL) / beta->__des);
    // if (p2.y > screenHeight)
    //     p2.y = screenHeight;
    middel = p2.y / 2;
    p1.y = (screenHeight / 2) - middel;
    p2.y = screenHeight / 2 + middel;
    int const_1 = p1.x + 2;

    p1.color = beta->color;

    while (p1.x < const_1)
    {
        p2.color = i;
        draw_____line(beta, p1, p2, st);
        p1.x++;
        p2.x++;
        i++;

        st++;
    }
}