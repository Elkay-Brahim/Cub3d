/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:24:07 by rrasezin          #+#    #+#             */
/*   Updated: 2023/08/01 13:28:07 by rrasezin         ###   ########.fr       */
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

int check_ext(char *name, char *ext)
{
    int     i;
    char    *extenction;

    i = ft_strlen(name);
    if (i <= 4)
        return (1);
    extenction = name + (i - 4);
    i = 0;
    while (extenction[i])
    {
        if (extenction[i] != ext[i])
            return (1);
        i++;
    }
    return (0);
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
            write(2, "invalid path identifier\n", 24);
            return (1);
        }
    }
    else
    {
        write(2, "invalid path identifier\n", 24);
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
            write(2, "invalid color identifier\n", 25);
            return (1);
        }
    }
    else
        return (1);
    if (map->f_color == -1 || map->c_color == -1)
    {
        write(2, "invalid color value\n", 20);
        return (1);
    }
    return (0);
}

int check_data(t_map *map)
{
    int fd;
    
    if (map->n_path == NULL || map->s_path == NULL || map->w_path == NULL ||\
        map->e_path == NULL || map->f_color == -2 || map->c_color == -2)
        return (1);
    if (check_ext(map->n_path, ".xpm") == 1 || check_ext(map->s_path, ".xpm") == 1 ||\
        check_ext(map->w_path, ".xpm") == 1 || check_ext(map->e_path, ".xpm") == 1)
        return (1);
    fd = open(map->n_path, O_RDONLY);
    if (fd == -1)
        return (1);
    close (fd);
    fd = open(map->s_path, O_RDONLY);
    if (fd == -1)
        return (1);
    close (fd);
    fd = open(map->w_path, O_RDONLY);
    if (fd == -1)
        return (1);
    fd = open(map->e_path, O_RDONLY);
    if (fd == -1)
        return (1);
    close (fd);
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
                    return(printf("Error extra border\n"));
                if ((j > 0 && map->map[j - 1][i] == 2) || (j < (map->height - 1) && map->map[j + 1][i] == 2))
                    return(printf("middel Y\n"));
                if ((i > 0 && map->map[j][i - 1] == 2) || (i < (map->width - 1) && map->map[j][i + 1] == 2))
                    return(printf("middel X\n"));
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
        write (2, "additonal data\n", 15);
        return (1);
    }
    map_2d = ft_split(line, '\n');
    final_map(map, map_2d);
    free_double(map_2d);
    if (chech_border(map) != 0)
        return (1);
    return (0);
}

int get_map_element(t_map *map, char *line, int type)
{
    char    **sp;

    line[ft_strlen(line ) -1] = '\0';
    sp = ft_split(line, ' ');
    if (!sp || sp[0] == NULL)
    {
        free_double(sp);
        write (2, "wrong element\n", 14);
        return (1);
    }
    if (type == 1 && check_path(map, sp) == 1)
    {
        free_double(sp);
        return (1);
    }
    if (type == 2 && check_color(map, sp) == 1)
    {
        free_double(sp);
        return (1);
    }
    free_double(sp);
    return (0);
}

int get_world(t_line *data, t_map *map)
{
    char    *map_line;

    if (data != NULL)
    {
        map_line = ft_calloc(1, 1);
        while (data != NULL)
        {
            map_line = ft_strjoin(map_line, data->line);
            data = data->next;
        }
        if (!map_line || check_map(map, map_line) != 0)
        {
            free(map_line);
            return (1);
        }
    }
    else
    {
        write (2, "-_- there is no world here\n", 27);
        return (1);
    }
    free(map_line);
    return (0);
}

t_map   *get_map(t_line *data)
{
    t_map   *map;

    map = ft_calloc(sizeof(t_map), 1);
    map->c_color = -2;
    map->f_color = -2;
    while (data->type != 3)
    {
        if (data->type != 0 && get_map_element(map, data->line, data->type) != 0)
        {
            free_map(map);
            return (NULL);
        }
        data = data->next;
        if (data == NULL)
            break;
    }
    if (check_data(map) != 0)
    {
        free_map(map);
        write(2, "invalid path\n", 13);
        return (NULL);
    }
    if (get_world(data, map) != 0)
    {
        free_map(map);
        return (NULL);
    }
    return (map);
}

int check_file(char *map_path)
{
    int fd;

    if (check_ext(map_path, ".cub") != 0)
    {
        write(2, "Error extention\n", 15);
        return (-1);
    } 
    fd = open(map_path, O_RDONLY);
    if (fd == -1)
    {
        write(2, "Error read map\n", 15);
        return (-1);
    } 
    return (fd);
}

t_map *littel_world(char *map_path)
{
    int     fd;
    t_line  *base_line;
    t_line  *tmp;
    t_map   *map;

    fd = check_file(map_path);
    if (fd == -1)
        return (NULL);
    base_line = get_data_map(fd);
    if (base_line == NULL)
    {
        write(2, "empty file\n", 11);
        close(fd);
        return (NULL);
    } 
    tmp = base_line;
    map = get_map(tmp);
    free_line(base_line);
    if (map != NULL)
    {
        print_map(map);
    }
    return (map);
}

// int main(int ac, char **av)
// {
//     (void)ac;
//     t_map *map = littel_world(av[1]);
//     if (map)
//         print_map(map);
//     while(1);
// }