/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:14:35 by bchifour          #+#    #+#             */
/*   Updated: 2023/07/25 18:14:38 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif
int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}
void	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	size_t	n;

	n = size * count;
	p = malloc(n);
	while (n--)
		*(p + n) = 0;
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (len_s1 + len_s2) + 1);
	if (!new)
		return (NULL);
	while (s1[j] != '\0')
		new[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	free (s1);
	return (new);
}

int	ft_strchr(char *s)
{
	int i;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}


char	*get_next(char *buffer)
{
	char	*next;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free (buffer);
		return (NULL);
	}
	next = ft_calloc ((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	while (buffer[i])
	{
		next[j++] = buffer[i++];
	}
	free (buffer);
	return (next);
}

char	*gett_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (*line == '\0')
	{
		free (line);
		line = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*buffer_perime;
	int			read_char;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_calloc (1, 1);
	buffer_perime = ft_calloc (BUFFER_SIZE + 1, sizeof(char));
	read_char = 1;
	while ((!(ft_strchr(buffer_perime)) && read_char != 0))
	{
		read_char = read (fd, buffer_perime, BUFFER_SIZE);
		if (read_char == -1)
		{
			free(buffer);
			free (buffer_perime);
			buffer = NULL;
			return (0);
		}
		buffer_perime[read_char] = '\0';
		buffer = ft_strjoin(buffer, buffer_perime);
	}
	free (buffer_perime);
	buffer_perime = gett_line(buffer);
	buffer = get_next(buffer);
	return (buffer_perime);
}