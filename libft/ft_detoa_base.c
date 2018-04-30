/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_detoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 16:02:49 by ddenkin           #+#    #+#             */
/*   Updated: 2017/12/17 16:46:15 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		transform(double *num, int base)
{
	int		exp;

	exp = 0;
	if (*num > 1 || *num < -1)
		while ((*num >= base || *num <= -base))
		{
			*num /= base;
			exp++;
		}
	else
		while (*num <= 1 && *num >= -1 && *num != 0)
		{
			*num *= base;
			exp--;
		}
	return (exp);
}

static char		*dexptoa(double num, int precision, int base)
{
	char	*res;
	int		i;

	if (precision <= 0)
		return (ft_strdup(""));
	if (num < 0)
		num = -num;
	num = ft_roundd_base(num, precision, base);
	res = (char *)malloc(sizeof(char) * (precision + 2));
	res[precision + 1] = 0;
	res[0] = '.';
	i = 0;
	while (i < precision)
	{
		num *= base;
		if (ft_abs((int)num % base) <= 9)
			res[i + 1] = ((int)num % base) + 48;
		else
			res[i + 1] = ft_abs(((int)num % base)) + 87;
		num -= ft_abs((int)num % base);
		i++;
	}
	return (res);
}

static char		*addexp(char *s, int isize)
{
	char	*res;
	char	*tmp1;
	char	*tmp2;

	tmp1 = (isize >= 0) ? ft_strdup("p+") : ft_strdup("p-");
	tmp2 = (isize >= 0) ? ft_itoa(isize) : ft_itoa(-isize);
	res = ft_strjoin(tmp1, tmp2);
	ft_strdel2(&tmp1, &tmp2);
	tmp1 = ft_strjoin(s, res);
	ft_strdel(&res);
	return (tmp1);
}

char			*ft_detoa_base(double num, int precision, int base)
{
	int		isize;
	double	exp;
	char	*res1;
	char	*res2;
	char	*res;

	isize = transform(&num, 2);
	res1 = ft_itoa_base((int)num, base);
	res2 = (num < 0) ? ft_strdup("-0") : ft_strdup("0x");
	(num < 0) ? res1[0] = 'x' : 1;
	res = ft_strjoin(res2, res1);
	ft_strdel2(&res1, &res2);
	res1 = res;
	exp = num - (int)num;
	res2 = dexptoa(exp, precision, base);
	res = ft_strjoin(res1, res2);
	ft_strdel2(&res1, &res2);
	res1 = res;
	res = addexp(res, isize);
	ft_strdel(&res1);
	return (res);
}
