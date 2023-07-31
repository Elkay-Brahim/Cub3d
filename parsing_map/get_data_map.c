/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:53:45 by rrasezin          #+#    #+#             */
/*   Updated: 2023/07/31 10:33:47 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    add_back(t_line **base, t_line *new)
{
    t_line *tmp;

    tmp = *base;
    if (*base == NULL)
        *base = new;
    else
    {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new;
    }
    return ;
}

int just_space(char *data)
{
    int i;

    i = 0;
    while (data[i] == ' ')
            i++;
    if (data[i] == '\n' || data[i] == '\0')
        return (0);
    return (3);
}

void    free_line(t_line *base)
{
    t_line  *tmp;

    tmp = base;
    while (base != NULL)
    {
        tmp = base->next;
        free(base->line);
        free(base);
        base = tmp;
    }
    return ;
}

void    free_map(t_map *map)
{
    if (map->map)
        free(map->map);
    if (map->n_path)
        free(map->n_path);
    if (map->s_path)
        free(map->s_path);
    if (map->w_path)
        free(map->w_path);
    if (map->e_path)
        free(map->e_path);
    free(map);
    return ;
}

t_line *get_data_map(int fd)
{
    t_line *base_line;
    t_line *line;
    char    *data;

    base_line = NULL;
    while (1)
    {
        data = get_next_line(fd);
        if (data == NULL)
            break;
        line = ft_calloc(sizeof(t_line), 1);
        line->line = data;
        if (ft_strchr(data, '/'))
            line->type = 1;
        else if (ft_strchr(data, ','))
            line->type = 2;
        else if (data[0] == '\n')
            line->type = 0;
        else
            line->type = just_space(data);
        line->next = NULL;
        add_back(&base_line, line);
    }
    return (base_line);
}