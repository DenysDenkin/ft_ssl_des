/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:33:19 by ddenkin           #+#    #+#             */
/*   Updated: 2018/02/18 18:35:41 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static char	*pad(char *str, size_t size)
{
	char	*pad;
	size_t	len;

	len = ft_strlen(str);
	if (len > size)
	{
		pad = (char *)malloc(sizeof(char) * (size + 1));
		pad[size] = 0;
		ft_strncpy(pad, str, size);
		str = pad;
		return (str);
	}
	pad = (char *)malloc(sizeof(char) * (size + 1 - len));
	pad[size - len] = 0;
	ft_memset(pad, '0', size - len);
	str = ft_strjoin(str, pad);
	return (str);
}

t_uberstr	*pad_str(t_arg *arg)
{
	t_uberstr	*res;
	char		byte;
	size_t		size;
	size_t		bonus;

	size = arg->str->size;
	res = (t_uberstr *)malloc(sizeof(t_uberstr));
	byte = (char)((size % 8 == 0) ? 0 : (8 - size % 8));
	size = (size % 8 == 0) ? size : (size / 8 + 1) * 8;
	bonus = ((size % 8 != 0 || byte != 0) && size != 0) ? 0 : 8;
	res->str = (char *)malloc(sizeof(char) * (size + bonus + 1));
	res->str[size + bonus] = 0;
	ft_strncpy(res->str, arg->str->str, arg->str->size);
	ft_memset(res->str + size - byte, byte, (size_t)byte);
	res->size = arg->str->size + byte;
	if (byte == 0)
	{
		ft_memset(res->str + size + byte, 8, bonus);
		res->size += bonus;
	}
	return (res);
}

void		input_arg(char *message, char **str, t_arg *arg, size_t size)
{
	if (*str == NULL)
	{
		ft_putstr(message);
		if ((get_next_line(arg->infd, &(*str)) <= 0))
			exit(255);
	}
	*str = pad(*str, size);
}

t_uberstr	*input_str(t_arg *arg)
{
	ssize_t		ret;
	t_uberstr	*temp;

	arg->str = t_uberdup("", 0);
	temp = t_uberdup("", 2048);
	if ((arg->str->str = ft_strdup("")) != 0)
		while ((ret = read(arg->infd, temp->str, 2048)) > 0)
		{
			arg->str->str = ft_strnjoin(arg->str->str, temp->str,\
					arg->str->size, (size_t)ret);
			arg->str->size += ret;
		}
	return (arg->str);
}
