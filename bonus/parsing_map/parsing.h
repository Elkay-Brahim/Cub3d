/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:24:23 by rrasezin          #+#    #+#             */
/*   Updated: 2023/08/05 10:35:43 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h"
# include "utils/utils.h"

// 1 path
// 2 color
// 3 data map

typedef struct s_line
{
	char			*line;
	int				type;
	struct s_line	*next;
}	t_line;

typedef struct s_parsing_map
{
	int		**map;
	int		direction;
	char	*n_path;
	char	*s_path;
	char	*w_path;
	char	*e_path;
	char	*door;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		f_color;
	int		c_color;
}		t_map_s;

char	*get_next_line(int fd);
t_line	*get_data_map(int fd);
void	free_line(t_line *base);
void	free_map(t_map_s *map);
t_map_s	*littel_world(char *map_path, int fd);
int		get_map_element(t_map_s *map, char *line, int type);
void	free_double(char **sp);
t_map_s	*get_map(t_line *data);
int		check_ext(char *name, char *ext);
int		get_world(t_line *data, t_map_s *map);
void	final_map(t_map_s *map, char **line);

#endif