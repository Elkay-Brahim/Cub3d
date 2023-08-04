/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:06:17 by rrasezin          #+#    #+#             */
/*   Updated: 2023/08/04 18:01:29 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_(size_t count, size_t size)
{
	void	*alloc;
	size_t	t;

	t = count * size;
	alloc = malloc(t);
	if (!alloc)
		return (NULL);
	while (t--)
		*(unsigned char *)(alloc + t) = '\0';
	return (alloc);
}

char	*ft_strchr_(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' || c == '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin_(char *s1, char *s2)
{
	char	*new;
	size_t	size;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	size = 0;
	if (!s1)
		return (NULL);
	size = ft_strlen_(s1) + ft_strlen_(s2);
	if (s1 || s2)
		size = size + 1;
	new = malloc(sizeof(char) * size);
	if (!new)
		return (NULL);
	while (s1[i] != '\0')
		new[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	free (s1);
	return (new);
}

size_t	ft_strlen_(const char *src)
{
	int	i;

	i = 0;
	while (src[i] != 0)
	{
		i++;
	}
	return (i);
}
