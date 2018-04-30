/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:32:13 by ddenkin           #+#    #+#             */
/*   Updated: 2018/02/18 18:35:26 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static char			get(unsigned char c)
{
	int			i;
	const char	*table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklm"

	"nopqrstuvwxyz0123456789+/";
	i = 0;
	while (table[i] != c && i < 64)
		i++;
	if (i == 64)
		return ('=');
	else
		return ((char)i);
}

static void			mutate_block(char *to, const unsigned char *from,
								int dec, size_t size)
{
	const char	*table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabc"

	"defghijklmnopqrstuvwxyz0123456789+/";
	if (dec == 0)
	{
		to[0] = table[from[0] >> 2];
		to[1] = table[((from[0] & 3) << 4) + (from[1] >> 4)];
		to[2] = (char)(((from[1] == 0 && from[2] == 0) || size < 2) ? '='
						: table[((from[1] & 15) << 2) + (from[2] / 64)]);
		to[3] = (char)((from[2] == 0 || to[2] == '=' || size < 3) ? '='
						: table[from[2] & 63]);
	}
	else
	{
		to[0] = (char)(get(from[0]) * 4 + get(from[1]) / 16);
		if (from[1] != 61 && from[2] != 61)
			to[1] = (char)(get(from[1]) % 16 * 16 + get(from[2]) / 4);
		else
			to[1] = 0;
		if (from[2] != 61 && from[3] != 61)
			to[2] = (char)(get(from[2]) % 4 * 64 + get(from[3]));
		else
			to[2] = 0;
	}
}

static t_uberstr	*encode(t_arg *arg)
{
	t_uberstr	*res;
	size_t		i;
	int			asize;
	int			k;

	res = (t_uberstr *)malloc(sizeof(t_uberstr));
	count_stuff(&asize, res, arg);
	i = ft_strlen(arg->str->str);
	while (i <= res->size)
		res->str[i++] = 0;
	i = 0;
	k = 0;
	while (i < arg->str->size)
	{
		if (i > 0 && (i / 3 * 4) % 64 == 0)
			res->str[i / 3 * 4 + k++] = '\n';
		mutate_block(res->str + (i / 3 * 4) + k, (const unsigned char *)
				(arg->str->str + i), 0, arg->str->size - i);
		i += 3;
	}
	res->str[res->size] = 0;
	i = 0;
	while (++i - 1 < res->size - asize)
		(res->str[i - 1] == '=') ? res->str[i - 1] = 'A' : 1;
	return (res);
}

static t_uberstr	*decode(t_arg *arg)
{
	t_uberstr	*res;
	size_t		i;
	int			k;

	res = (t_uberstr *)malloc(sizeof(t_uberstr));
	res->size = (ft_strlenn(arg->str->str, arg->str->size)) * 3 / 4;
	res->str = (char *)malloc(sizeof(char) * (res->size + 1));
	i = 0;
	k = 0;
	while (i < ft_strlenn(arg->str->str, arg->str->size))
	{
		if (i != 0 && i % 64 == 0)
			k++;
		mutate_block(res->str + i * 3 / 4, (const unsigned char *)
				(arg->str->str + i + k), 1, arg->str->size - 4 * i - k);
		i += 4;
	}
	res->str[res->size] = 0;
	return (res);
}

t_uberstr			*base64(t_arg *arg)
{
	if (!arg->str)
		arg->str = input_str(arg);
	if (arg->flg->enc_mode == 1)
		return (encode(arg));
	else
		return (decode(arg));
}
