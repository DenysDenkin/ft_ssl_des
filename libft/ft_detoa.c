/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_detoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 16:21:00 by ddenkin           #+#    #+#             */
/*   Updated: 2017/12/15 18:52:37 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		transform(double *num)
{
	int		exp;

	exp = 0;
	if (*num > 1 || *num < -1)
		while ((*num >= 10 || *num <= -10))
		{
			*num /= 10;
			exp++;
		}
	else
		while (*num <= 1 && *num >= -1 && *num != 0)
		{
			*num *= 10;
			exp--;
		}
	return (exp);
}

static char		*dexptoa(double num, int precision)
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

static char		*addexp(char *s, int isize)
{
	char	*res;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = (isize >= 0) ? ft_strdup("e+") : ft_strdup("e-");
	tmp2 = (isize >= 0) ? ft_itoa(isize) : ft_itoa(-isize);
	if (isize >= -9 && isize <= 9)
	{
		res = ft_strdup("0");
		tmp3 = ft_strjoin(res, tmp2);
		ft_strdel2(&res, &tmp2);
		tmp2 = tmp3;
	}
	res = ft_strjoin(tmp1, tmp2);
	ft_strdel2(&tmp1, &tmp2);
	tmp1 = ft_strjoin(s, res);
	ft_strdel(&res);
	return (tmp1);
}

char			*ft_detoa(double num, int precision)
{
	int		isize;
	double	exp;
	char	*res1;
	char	*res2;
	char	*res;

	isize = transform(&num);
	res1 = ft_itoa((int)num);
	exp = num - (int)num;
	res2 = dexptoa(exp, precision);
	res = ft_strjoin(res1, res2);
	ft_strdel2(&res1, &res2);
	res1 = res;
	res = addexp(res, isize);
	ft_strdel(&res1);
	return (res);
}
