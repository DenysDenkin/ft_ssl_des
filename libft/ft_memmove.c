/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:05:01 by ddenkin           #+#    #+#             */
/*   Updated: 2017/11/02 15:23:11 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;

	i = -1;
	if (dst < src)
		while (++i < len)
			((char *)dst)[i] = ((char *)src)[i];
	else
	{
		i = len + 1;
		while (--i > 0)
			((char *)dst)[i - 1] = ((char *)src)[i - 1];
	}
	return (dst);
}
