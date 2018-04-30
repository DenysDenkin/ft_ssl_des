/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:33:05 by ddenkin           #+#    #+#             */
/*   Updated: 2018/02/18 19:06:09 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

t_uberstr			*str_to_hex(const char *arg, size_t size)
{
	unsigned long	i;
	unsigned char	*str;
	t_uberstr		*res;

	i = 0;
	str = (unsigned char *)arg;
	res = (t_uberstr *)malloc(sizeof(t_uberstr));
	res->size = size * 2;
	res->str = (char *)malloc(sizeof(char) * (res->size + 1));
	while (i < size * 2)
	{
		res->str[i * 2] = (str[i] / 16 < 10) ? (char)(str[i] / 16 + 48) :\
			(char)(str[i] / 16 + 55);
		res->str[i * 2 + 1] = (str[i] % 16 < 10) ? (char)(str[i] % 16 + 48) :\
			(char)(str[i] % 16 + 55);
		i++;
	}
	res->str[size * 2] = 0;
	return (res);
}

char				hex_to_char(const char hex)
{
	if (hex <= '9' && hex >= '0')
		return (char)(hex - 48);
	else if (hex >= 'A' && hex <= 'Z')
		return (char)(hex - 55);
	else if (hex >= 'a' && hex <= 'z')
		return (char)(hex - 87);
	return (0);
}

t_uberstr			*hex_to_str(const char *hex, size_t size)
{
	size_t		i;
	t_uberstr	*res;

	i = 0;
	res = (t_uberstr *)malloc(sizeof(t_uberstr));
	res->size = size / 2;
	res->str = (char *)malloc(sizeof(char) * (res->size + 1));
	while (i < size)
	{
		res->str[i / 2] = 0;
		res->str[i / 2] += hex_to_char(hex[i]) * 16;
		res->str[i / 2] += hex_to_char(hex[i + 1]);
		i += 2;
	}
	res->str[size / 2] = 0;
	return (res);
}

void				count_stuff(int *asize, t_uberstr *res, t_arg *arg)
{
	res->size = (arg->str->size + 2) / 3 * 4;
	res->size += (res->size - 1) / 64;
	res->str = (char *)malloc(sizeof(char) * (res->size + 1));
	(arg->str->size % 3 == 0) ? *asize = 0 : 1;
	(arg->str->size % 3 == 1) ? *asize = 2 : 1;
	(arg->str->size % 3 == 2) ? *asize = 1 : 1;
}

size_t				ft_strlenn(const char *str, size_t size)
{
	size_t	res;
	size_t	i;

	res = 0;
	i = 0;
	while (i < size)
	{
		if (str[i] != '=' && str[i] != '\n')
			res++;
		i++;
	}
	return (res);
}
