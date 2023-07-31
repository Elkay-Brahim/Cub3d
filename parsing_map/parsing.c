/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:24:07 by rrasezin          #+#    #+#             */
/*   Updated: 2023/07/31 14:59:10 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    free_double(char **sp)
{
    int i;

    i = 0;
    while(sp[i] != NULL)
    {
        free(sp[i]);
        i++;
    }
    free(sp);
}

int    check_path(t_map *map, char **sp)
{
    if (ft_strlen(sp[0]) == 2 && sp[1] != NULL && sp[2] == NULL)
    {
        if (sp[0][0] == 'N' && sp[0][1] == 'O' && !map->n_path)
            map->n_path = ft_strdup(sp[1]);
        else if (sp[0][0] == 'S' && sp[0][1] == 'O' && !map->s_path)
            map->s_path = ft_strdup(sp[1]);
        else if (sp[0][0] == 'W' && sp[0][1] == 'E' && !map->w_path)
            map->w_path = ft_strdup(sp[1]);
        else if (sp[0][0] == 'E' && sp[0][1] == 'A' && !map->e_path)
            map->e_path = ft_strdup(sp[1]);
        else
        {
            write(2, "Error\n", 6);
            return (1);
        }
    }
    else
    {
        write(2, "Error\n", 6);
        return (1);
    }
    return (0);
}

int rgb_to_int(char *color)
{
    char    **rgb;
    int     int_color;
    int     i;
    int     p;
    int     nb;

    i = 0;
    int_color = 0;
    p = 0;
    rgb = ft_split(color, ',');
    while (rgb[i] != NULL)
    {
        nb = mini_atoi(rgb[i]);
        if (nb == -1)
        {
            free_double(rgb);
            return (-1);
        }
        int_color = (int_color << p) + nb;
        p = 8;
        i++;
    }
    free_double(rgb);
    if (i != 3)
        return (-1);
    return(int_color);
}

int check_color(t_map *map, char **sp)
{
    if (ft_strlen(sp[0]) == 1 && sp[1] != NULL && sp[2] == NULL)
    {
        if (sp[0][0] == 'F' && map->f_color == -2)
            map->f_color = rgb_to_int(sp[1]);
        else if (sp[0][0] == 'C' && map->c_color == -2)
            map->c_color = rgb_to_int(sp[1]);
        else
        {
            printf("not valid identifier\n");
            return (1);
        }
    }
    else
    {
        printf("Error split\n");
        return (1);
    }
    if (map->f_color == -1 || map->c_color == -1)
    {
        printf("invalid nbr of color\n");
        return (1);
    }
    return (0);
}

int check_data(t_map *map)
{
    if (map->n_path == NULL)
        return (1);
    if (map->s_path == NULL)
        return (1);
    if (map->w_path == NULL)
        return (1);
    if (map->e_path == NULL)
        return (1);
    if (map->f_color == -2)
        return (1);
    if (map->c_color == -2)
        return (1);
    return (0);
}

int check_content(char *line, int *d)
{
    int i;
    int dir;

    i = 0;
    dir = 0;
    while (line[i] != '\0')
    {
        if (!(line[i] == '1' || line[i] == '0' || line[i] == 'D' || line[i] == '\n' || line[i] == ' '))
        {
            if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'W'\
                || line[i] == 'E') && dir == 0)
                dir = line[i];
            else
                return (1);
        }
        i++;
    }
    if (dir == 0)
        return (1);
    *d = dir;
    return (0);
}

void    print_map(t_map *map)
{
    int i = 0;
    int j = 0;

    printf("NO : %s\n", map->n_path);
    printf("SO : %s\n", map->s_path);
    printf("WE : %s\n", map->w_path);
    printf("EA : %s\n", map->e_path);
    printf("F : %d\n", map->f_color);
    printf("C : %d\n", map->c_color);
    printf("Deriction : %c\n", map->direction);
    printf("width : %d\n", map->width);
    printf("height : %d\n", map->height);
    printf("player : (%d, %d)\n", map->player_x, map->player_y);
    while (j < map->height)
    {
        printf ("[ ");
        while (i < map->width)
        {
            printf ("%d, ", map->map[j][i]);
            i++;
        }
        i = 0;
        j++;
        printf("]\n");
    }
}

void    final_map(t_map *map, char **line)
{
    int tmp;
    int i;
    int j;
    int size;

    tmp = 0;
    i = 0;
    j = 0;
    while (line[i] != NULL)
    {
        if (line[i][0] != '\n')
        {
            map->height++;
            tmp = ft_strlen(line[i]);
            if (map->width < tmp)
                map->width = tmp;
        }
        i++;
    }
    i = 0;
    tmp = 0;
    map->map = ft_calloc(sizeof(int *), map->height);
    while (i < map->height)
    {
        if(line[j][tmp] != '\n')
        {
            map->map[i] = ft_calloc(sizeof(int), map->width);
            size = ft_strlen(line[j]);
            while (tmp < map->width)
            {
                if (tmp < size)
                {
                    if (line[j][tmp] && line[j][tmp] == '1')
                        map->map[i][tmp] = 1;
                    else if (line[j][tmp] && line[j][tmp] == '0')
                        map->map[i][tmp] = 0;
                    else if (line[j][tmp] && line[j][tmp] == ' ')
                        map->map[i][tmp] = 2;
                    else if (line[j][tmp] && line[j][tmp] == 'D')
                        map->map[i][tmp] = 3;
                    else if (line[j][tmp] && line[j][tmp] == map->direction)
                    {
                        map->map[i][tmp] = 5;
                        map->player_x = tmp;
                        map->player_y = i;
                    }
                }
                else
                    map->map[i][tmp] = 2;
                tmp++;
            } 
            i++;
            tmp = 0;
        }
        j++;
    }
    // print_map(map);
}

int chech_border(t_map *map)
{
    int i;
    int j;

    j = 0;
    while (j < map->height)
    {
        i = 0;
        while (i < map->width)
        {
            if (map->map[j][i] == 5 || map->map[j][i] == 0 || map->map[j][i] == 3)
            {
                if (!(j > 0 && j < (map->height - 1) && i > 0 && i < (map->width - 1)))
                    exit(printf("Error extra border\n"));
                if ((j > 0 && map->map[j - 1][i] == 2) || (j < (map->height - 1) && map->map[j + 1][i] == 2))
                    exit(printf("middel Y\n"));
                if ((i > 0 && map->map[j][i - 1] == 2) || (i < (map->width - 1) && map->map[j][i + 1] == 2))
                    exit(printf("middel X\n"));
            }
            i++;
        }
        j++;
    }
    return (0);
}

int check_map(t_map *map, char* line)
{
    int     i;
    char    **map_2d;
    (void)map_2d;

    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '\n' && line[i + 1] == '\n')
            break;
        i++;
    }
    while (line[i] && line[i] == '\n')
        i++;
    if (line[i] != '\0' || check_content(line, &map->direction) != 0)
    {
        printf("additonal data\n");
        exit(1);
    }
    map_2d = ft_split(line, '\n');
    final_map(map, map_2d);
    chech_border(map);
    return (0);
}


t_map   *get_map(t_line *data)
{
    int i;
    t_map   *map;
    char    **sp;
    t_line  *save;
    char    *map_line;

    save = data;
    map = ft_calloc(sizeof(t_map), 1);
    map->c_color = -2;
    map->f_color = -2;
    i = 0;
    while (data->type != 3)
    {
        if (data->type != 0)
        {
            data->line[ft_strlen(data->line ) -1] = '\0';
            sp = ft_split(data->line, ' ');
            if (!sp || sp[0] == NULL)
            {
                printf("Error split\n");
                exit (1);
            }
            if (data->type == 1)
            {
                if (check_path(map, sp) == 1)
                {
                    printf("Error path\n");
                    exit(1);
                }
            }
            if (data->type == 2)
            {
                if (check_color(map, sp) == 1)
                {
                    printf("Error color\n");
                    exit(1);
                }
            }
            free_double(sp);
        }
        data = data->next;
        if (data == NULL)
            break;
    }
    if (check_data(map) != 0)
    {
        free_line(data);
        free_map(map);
        printf ("data not complet\n");
        exit(1); //most change it
    }
    if (data != NULL)
    {
        map_line = ft_calloc(1, 1);
        while (data != NULL)
        {
            map_line = ft_strjoin(map_line, data->line);
            data = data->next;
        }
        // printf("%s", map_line);
        if (!map_line || check_map(map, map_line) != 0)
            return (NULL);
    }
    return (map);
}

int main(int ac, char **av)
{
    (void) ac;
    (void) av;
    int     fd;
    t_line *base_line;

    if (ac != 2)
    {
        write(2, "need name of file\n", 18);
        return (0);
    }
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
    {
        write(2, "Error read map\n", 15);
        return (1);
    } 
    base_line = get_data_map(fd);
    if (base_line == NULL)
    {
        write(2, "some wrongs [!]\n", 9);
        close(fd);
        exit(1);
    }
    t_map *map = get_map(base_line);
    (void)map;
    // while (1)
    // {
    //     printf("%d    | %s", base_line->type, base_line->line);
    //     base_line = base_line->next;
    //     if (base_line == NULL)
    //         break;
    // }
    // printf("map->n_path %s\n", map->n_path);
    // printf("map->s_path %s\n", map->s_path);
    // printf("map->w_path %s\n", map->w_path);
    // printf("map->e_path %s\n", map->e_path);
    // printf("map->f_color %d\n", map->f_color);
    // printf("map->c_color %d\n", map->c_color);
    
    
}