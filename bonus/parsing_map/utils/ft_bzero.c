/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:58:38 by rrasezin          #+#    #+#             */
/*   Updated: 2023/07/31 15:15:35 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h" 

void	ft_bzero(void *src, size_t len)
{
	unsigned char	*dest;

	dest = (unsigned char *)src;
	while (len)
	{
		*dest = 0;
		dest++;
		len--;
	}
}
