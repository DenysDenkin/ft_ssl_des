/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 16:24:22 by ddenkin           #+#    #+#             */
/*   Updated: 2017/12/17 17:03:25 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			i_size(double n)
{
	int			i;
	double		temp;

	i = 0;
	if (n >= 0)
		temp = n;
	else
	{
		temp = -n;
		i++;
	}
	while ((temp /= 10) >= 1)
		i++;
	return (i + 1);
}

static char			*dmtoa(double num, int isize)
{
	char	*res;
	int		i;
	int		start;

	res = (char *)malloc(sizeof(char) * (isize + 1));
	res[isize] = 0;
	start = 0;
	if (num < 0)
	{
		res[0] = '-';
		start = 1;
	}
	i = isize;
	while (i > start)
	{
		if (num > 0)
			res[i - 1] = (intmax_t)num % 10 + 48;
		else
			res[i - 1] = 48 - (intmax_t)num % 10;
		num /= 10;
		i--;
	}
	return (res);
}

static char			*detoa(double num, int precision)
{
	char	*res;
	int		i;

	if (precision <= 0)
		return (ft_strdup(""));
	if (num < 0)
		num = -num;
	num = ft_roundd(num, precision);
	res = (char *)malloc(sizeof(char) * (precision + 2));
	res[precision + 1] = 0;
	res[0] = '.';
	i = 0;
	while (i < precision)
	{
		num *= 10;
		res[i + 1] = ((int)num % 10) + 48;
		num -= res[i + 1] - 48;
		i++;
	}
	return (res);
}

static double		get_mant(double num, int isize)
{
	int		pow;
	double	res;
	double	temp;

	res = 0;
	if (num < 0)
		isize--;
	pow = isize;
	while (num >= 1 || num <= -1)
	{
		temp = (intmax_t)num / ft_pow(10, pow - 1) * ft_pow(10, pow - 1);
		res += temp;
		num -= temp;
		pow -= 19;
		if (pow <= 0)
			pow = 1;
	}
	return (res);
}

char				*ft_dtoa(double num, int precision)
{
	int		isize;
	double	mant;
	char	*res1;
	char	*res2;
	char	*res;

	isize = i_size(num);
	mant = get_mant(num, isize);
	mant = (num < 0) ? num - mant : mant - num;
	if (precision == 0 && ft_abs((int)(mant * 10)) >= 5)
		num++;
	res1 = dmtoa(num, isize);
	res2 = detoa(mant, precision);
	res = ft_strjoin(res1, res2);
	ft_strdel2(&res1, &res2);
	return (res);
}
