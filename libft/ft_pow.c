/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:56:51 by ddenkin           #+#    #+#             */
/*   Updated: 2017/12/15 15:58:40 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_pow(double x, int y)
{
	double	res;
	double	i;

	res = 1;
	i = 0;
	if (y >= 0)
		while (i < y)
		{
			res *= x;
			i++;
		}
	else
		while (i < ft_abs(y))
		{
			res *= 1 / x;
			i++;
		}
	return (res);
}
