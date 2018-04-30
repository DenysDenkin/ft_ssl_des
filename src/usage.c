/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:33:23 by ddenkin           #+#    #+#             */
/*   Updated: 2018/02/18 18:35:44 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

t_uberstr	*usage(t_arg *arg)
{
	ft_putstr("ft_ssl: Error: '");
	ft_putstr(arg->comm);
	ft_putstr("' is an invalid command.\n\n"
	"Standard commands:\n"
	"\n"
	"Message Digest commands:\n"
	"\n"
	"Cipher commands:\n"
	"base64\n"
	"des\n"
	"des-ecb\n"
	"des-cbc\n"
	"des3\n"
	"des3-ecb\n"
	"des3-cbc\n");
	return (NULL);
}
