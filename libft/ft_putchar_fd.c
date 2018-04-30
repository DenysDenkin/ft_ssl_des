/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 20:04:26 by ddenkin           #+#    #+#             */
/*   Updated: 2017/12/08 18:55:03 by ddenkin          ###   ########.fr       */
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

int			ft_putchar_fd_h(unsigned int ch, int fd, int size,\
		unsigned int *mask)
{
	unsigned char byte;

	if (size <= 16)
	{
		byte = (ch >> 12) | (mask[2] >> 16);
		write(fd, &byte, 1);
		byte = (((ch >> 6) << 26) >> 26) | (((mask[2] >> 8) << 24) >> 24);
		write(fd, &byte, 1);
		byte = ((ch << 26) >> 26) | ((mask[2] << 24) >> 24);
		write(fd, &byte, 1);
		return (3);
	}
	else
	{
		byte = (ch >> 18) | (mask[3] >> 24);
		write(fd, &byte, 1);
		byte = (((ch >> 12) << 26) >> 26) | (((mask[3] >> 16) << 24) >> 24);
		write(fd, &byte, 1);
		byte = (((ch >> 6) << 26) >> 26) | (((mask[3] >> 8) << 24) >> 24);
		write(fd, &byte, 1);
		byte = ((ch >> 26) << 26) | ((mask[3] << 24) >> 24);
		write(fd, &byte, 1);
		return (4);
	}
}

int			ft_putchar_fd(unsigned int ch, int fd)
{
	int				size;
	unsigned int	mask[4];
	unsigned char	byte;

	mask[0] = 0;
	mask[1] = 49280;
	mask[2] = 14712960;
	mask[3] = 4034953344;
	size = intsize(ch);
	if (size <= 7)
	{
		byte = ch;
		write(fd, &byte, 1);
		return (1);
	}
	else if (size <= 11)
	{
		byte = (ch >> 6) | (mask[1] >> 8);
		write(fd, &byte, 1);
		byte = ((ch << 26) >> 26) | ((mask[1] << 24) >> 24);
		write(fd, &byte, 1);
		return (2);
	}
	else
		return (ft_putchar_fd_h(ch, fd, size, mask));
}
