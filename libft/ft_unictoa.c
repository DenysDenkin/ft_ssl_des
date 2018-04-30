/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unictoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 20:23:14 by ddenkin           #+#    #+#             */
/*   Updated: 2017/12/08 18:57:33 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intsize(int ch)
{
	int i;

	i = 0;
	if (ch < 0)
		ch = -ch - 1;
	while (ch > 0)
	{
		i++;
		ch = ch >> 1;
	}
	return (i);
}

static int	ft_unictoa_h(char *res, unsigned int ch, int maxsize,\
		unsigned int *mask)
{
	int				size;
	unsigned char	byte;

	size = intsize(ch);
	if (size <= 16 && maxsize >= 3)
	{
		byte = (ch >> 12) | (mask[2] >> 16);
		*res++ = byte;
		byte = (((ch >> 6) << 26) >> 26) | (((mask[2] >> 8) << 24) >> 24);
		*res++ = byte;
		byte = ((ch << 26) >> 26) | ((mask[2] << 24) >> 24);
		*res++ = byte;
		return (3);
	}
	if (maxsize < 4)
		return (4);
	byte = (ch >> 18) | (mask[3] >> 24);
	*res++ = byte;
	byte = (((ch >> 12) << 26) >> 26) | (((mask[3] >> 16) << 24) >> 24);
	*res++ = byte;
	byte = (((ch >> 6) << 26) >> 26) | (((mask[3] >> 8) << 24) >> 24);
	*res++ = byte;
	byte = ((ch >> 26) << 26) | ((mask[3] << 24) >> 24);
	*res++ = byte;
	return (4);
}

int			ft_unictoa(char *res, unsigned int ch, int maxsize)
{
	int				size;
	unsigned int	mask[4];
	unsigned char	byte;

	mask[0] = 0;
	mask[1] = 49280;
	mask[2] = 14712960;
	mask[3] = 4034953344;
	size = intsize(ch);
	if (size <= 7 && maxsize >= 1)
	{
		byte = ch;
		*res++ = byte;
		return (1);
	}
	if (size <= 11 && maxsize >= 2)
	{
		byte = (ch >> 6) | (mask[1] >> 8);
		*res++ = byte;
		byte = ((ch << 26) >> 26) | ((mask[1] << 24) >> 24);
		*res++ = byte;
		return (2);
	}
	return (ft_unictoa_h(res, ch, maxsize, mask));
}
