/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:52:23 by rrasezin          #+#    #+#             */
/*   Updated: 2023/07/29 18:52:30 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*retval;
	size_t	t;

	t = count * size;
	retval = malloc(t);
	if (!retval)
		return (NULL);
	ft_bzero(retval, t);
	return (retval);
}
