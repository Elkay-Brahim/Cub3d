/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:51:16 by rrasezin          #+#    #+#             */
/*   Updated: 2023/07/31 15:15:46 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
// # include "get_next_line/get_next_line.h"

void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *src, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
int	    mini_atoi(char *data);
char	*ft_strjoin(char *s1, char *s2);

#endif