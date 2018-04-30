/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:45:28 by ddenkin           #+#    #+#             */
/*   Updated: 2017/12/08 18:46:49 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(unsigned long long n, int base)
{
	int					i;
	unsigned long long	temp;

	i = 0;
	temp = n;
	while ((temp /= base) > 0)
		i++;
	return (i + 1);
}

static char	*myutoa(unsigned long long n, int size, int base)
{
	int					i;
	int					end;
	unsigned long long	temp;
	char				*res;

	if (!(res = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	res[size] = '\0';
	end = 0;
	temp = n;
	i = size;
	while (--i >= end)
	{
		res[i] = (temp % base < 10) ? (temp % base) + 48 : (temp % base) + 87;
		temp /= base;
	}
	return (res);
}

char		*ft_ulltoa_base(unsigned long long n, int base)
{
	int		size;
	char	*res;

	size = count_size(n, base);
	res = myutoa(n, size, base);
	return (res);
}
