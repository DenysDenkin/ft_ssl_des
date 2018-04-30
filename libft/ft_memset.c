/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 19:47:56 by ddenkin           #+#    #+#             */
/*   Updated: 2017/11/30 17:55:20 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	*b1;

	i = 0;
	c1 = (unsigned char)c;
	b1 = (unsigned char *)b;
	while (i < len)
		b1[i++] = c1;
	return (b1);
}
