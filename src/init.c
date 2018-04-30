/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:33:16 by ddenkin           #+#    #+#             */
/*   Updated: 2018/02/18 18:35:39 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

t_arg	*init_arg(void)
{
	t_arg	*arg;

	arg = (t_arg *)malloc(sizeof(t_arg));
	arg->key = NULL;
	arg->str = NULL;
	arg->iv = NULL;
	arg->infd = 0;
	arg->outfd = 1;
	arg->comm = NULL;
	arg->outname = NULL;
	arg->inname = NULL;
	arg->flg = (t_flags *)malloc(sizeof(t_flags));
	arg->flg->enc_mode = 1;
	arg->flg->a = 0;
	arg->flg->i = 0;
	arg->flg->o = 0;
	arg->flg->sec_mode = 0;
	return (arg);
}
