/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 17:01:09 by ddenkin           #+#    #+#             */
/*   Updated: 2018/02/18 19:12:03 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_spaces(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (0);
	if (c == '\r' || c == '\v' || c == '\f')
		return (0);
	return (1);
}

intmax_t		ft_atoi_base(const char *str, int base)
{
	int				i;
	int				neg;
	uintmax_t		res;

	i = 0;
	neg = 1;
	res = 0;
	while (check_spaces(str[i]) == 0)
		i++;
	(str[i] == '-') ? neg = -1 : 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while ((str[i] >= 48 && str[i] <= 57) || ft_isalpha(str[i]))
	{
		res *= base;
		(str[i] >= '0' && str[i] <= '9') ? res += (str[i] - 48) : 1;
		(str[i] >= 'a' && str[i] <= 'z') ? res += (str[i] - 87) : 1;
		(str[i] >= 'A' && str[i] <= 'Z') ? res += (str[i] - 55) : 1;
		if ((res > 9223372036854775808U || i > 18) && neg == -1)
			return (0);
		if ((res > 9223372036854775807U || i > 18) && neg == 1)
			return (-1);
		i++;
	}
	return (res * neg);
}
