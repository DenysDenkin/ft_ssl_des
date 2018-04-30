/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:33:11 by ddenkin           #+#    #+#             */
/*   Updated: 2018/02/18 18:35:38 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

t_uberstr		*t_uberdup(char *str, size_t size)
{
	t_uberstr	*res;

	res = (t_uberstr *)malloc(sizeof(t_uberstr));
	if (size > 0 && str)
		res->str = ft_strndup(str, size);
	else if (str)
		res->str = ft_strdup(str);
	res->size = size;
	return (res);
}

char			**get_keys(t_arg *arg)
{
	char	**res;
	char	*temp;

	res = (char **)malloc(sizeof(char *) * 3);
	res[0] = ft_strndup(arg->key, 16);
	res[1] = strndup(arg->key + 16, 16);
	res[2] = strndup(arg->key + 32, 16);
	if (arg->flg->enc_mode == 0)
	{
		temp = res[0];
		res[0] = res[2];
		res[2] = temp;
	}
	return (res);
}

unsigned long	rotl(const unsigned long value, int shift)
{
	return (value << (36 + shift) >> 36) | (value >> (28 - shift));
}
