/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:32:48 by ddenkin           #+#    #+#             */
/*   Updated: 2018/02/18 18:35:30 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

unsigned long			*gen_blocks(char *str, size_t blocks)
{
	unsigned long	*res;
	size_t			i;

	res = (unsigned long *)malloc(sizeof(unsigned long) * blocks);
	i = 0;
	while (i < blocks)
	{
		res[i] = ft_atou_base(str + 16 * i, 16);
		i++;
	}
	return (res);
}

static unsigned long	*subdes(t_arg *arg, unsigned long *plain, size_t blocks)
{
	unsigned long	*subkeys;
	unsigned long	*cyph;
	unsigned long	*temp;
	size_t			i;

	(arg->flg->sec_mode == 1 && arg->flg->enc_mode == 1) ?\
			plain[0] ^= ft_atou_base(arg->iv, 16) : 1;
	subkeys = generate_keys(ft_atou_base(arg->key, 16));
	temp = (unsigned long *)malloc(sizeof(unsigned long) * (blocks));
	i = 0;
	while (i < blocks)
	{
		(arg->flg->enc_mode == 1 && arg->flg->sec_mode == 1 && i > 0) ?
				plain[i] ^= temp[i - 1] : 1;
		temp[i] = work_blocks(arg, plain[i], subkeys);
		(arg->flg->enc_mode == 0 && arg->flg->sec_mode == 1 && i > 0) ?
				temp[i] ^= plain[i - 1] : 1;
		i++;
	}
	cyph = temp;
	(arg->flg->sec_mode == 1 && arg->flg->enc_mode == 0) ?\
			cyph[0] ^= ft_atou_base(arg->iv, 16) : 1;
	return (cyph);
}

t_uberstr				*handle_input(t_arg *arg, size_t keysize)
{
	t_uberstr		*temp;

	input_arg("enter key in hex: ", &arg->key, arg, keysize);
	if (arg->flg->sec_mode == 1)
		input_arg("enter initial vector: ", &arg->iv, arg, 16);
	if (!arg->str)
		arg->str = input_str(arg);
	arg->str = (arg->flg->enc_mode == 1) ? pad_str(arg) : arg->str;
	temp = str_to_hex(arg->str->str, arg->str->size);
	return (temp);
}

t_uberstr				*des(t_arg *arg)
{
	t_uberstr		*temp;
	unsigned long	*blocks;
	size_t			i;
	char			*meh;
	unsigned long	tt;

	temp = handle_input(arg, 16);
	tt = ((temp->size - 1) / 16) + 1;
	blocks = gen_blocks(temp->str, tt);
	ft_strdel(&temp->str);
	free(temp);
	blocks = subdes(arg, blocks, tt);
	temp = t_uberdup("", 0);
	i = 0;
	while (i < ((arg->str->size - 1) / 8) + 1)
	{
		meh = ft_utoa_base(blocks[i], 16);
		temp->str = ft_strnjoin(temp->str, meh, temp->size, ft_strlen(meh));
		temp->size += ft_strlen(meh);
		i++;
	}
	temp = hex_to_str(temp->str, temp->size);
	return (temp);
}

t_uberstr				*descbc(t_arg *arg)
{
	arg->flg->sec_mode = 1;
	return (des(arg));
}
