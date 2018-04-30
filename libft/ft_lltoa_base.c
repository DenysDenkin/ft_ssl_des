/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 19:15:03 by ddenkin           #+#    #+#             */
/*   Updated: 2017/12/08 18:44:28 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(long long n, int base)
{
	int					i;
	unsigned long long	temp;

	i = 0;
	if (n >= 0)
		temp = n;
	else
	{
		temp = -n;
		i = 1;
	}
	while ((temp /= base) > 0)
		i++;
	return (i + 1);
}

static char	*myitoa(long long n, int size, int base)
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
	if (n < 0)
	{
		res[0] = '-';
		temp = -n;
		end = 1;
	}
	i = size;
	while (--i >= end)
	{
		res[i] = (temp % base < 10) ? (temp % base) + 48 : (temp % base) + 87;
		temp /= base;
	}
	return (res);
}

char		*ft_lltoa_base(long long n, int base)
{
	int		size;
	char	*res;

	size = count_size(n, base);
	res = myitoa(n, size, base);
	return (res);
}
