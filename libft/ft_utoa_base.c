/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 19:10:14 by ddenkin           #+#    #+#             */
/*   Updated: 2017/12/08 18:42:48 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(uintmax_t n, int base)
{
	int					i;
	uintmax_t			temp;

	i = 0;
	temp = n;
	while ((temp /= base) > 0)
		i++;
	return (i + 1);
}

static char	*myutoa(uintmax_t n, int size, int base)
{
	int					i;
	int					end;
	uintmax_t			temp;
	char				*res;

	if (!(res = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	res[size] = '\0';
	end = 0;
	temp = n;
	i = size;
	while (--i >= end)
	{
		res[i] = (char)((temp % base < 10) ? (temp % base) + 48 :\
				(temp % base) + 55);
		temp /= base;
	}
	return (res);
}

char		*ft_utoa_base(uintmax_t n, int base)
{
	int		size;
	char	*res;
	char	*temp;

	size = count_size(n, base);
	res = myutoa(n, size, base);
	if (ft_strlen(res) < 16)
	{
		temp = (char *)malloc(sizeof(char) * (17 - ft_strlen(res)));
		ft_memset(temp, '0', 16 - ft_strlen(res));
		temp[16 - ft_strlen(res)] = 0;
		res = ft_strjoin(temp, res);
	}
	return (res);
}
