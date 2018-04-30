/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 16:27:16 by ddenkin           #+#    #+#             */
/*   Updated: 2017/11/30 17:04:33 by ddenkin          ###   ########.fr       */
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

int				ft_atoi(const char *str)
{
	int				i;
	int				neg;
	size_t			res;

	i = 0;
	neg = 1;
	res = 0;
	while (check_spaces(str[i]) == 0)
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res *= 10;
		res += (str[i] - 48);
		if ((res > 9223372036854775808U || i > 18) && neg == -1)
			return (0);
		if ((res > 9223372036854775807U || i > 18) && neg == 1)
			return (-1);
		i++;
	}
	return (res * neg);
}
