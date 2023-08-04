/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 10:29:44 by rrasezin          #+#    #+#             */
/*   Updated: 2023/07/30 14:39:57 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	mini_atoi(char *data)
{
	int		i;
	int		result;

	i = 0;
	result = 0;
	while (data[i] >= '0' && data[i] <= '9')
	{
		result = result * 10 + data[i++] - '0';
		if (result > 255)
			return (-1);
	}
	if (data[i] != '\0')
		return (-1);
	return (result);
}
