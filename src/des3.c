/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:32:54 by ddenkin           #+#    #+#             */
/*   Updated: 2018/02/18 19:10:06 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static unsigned long	**keygen(t_arg *arg)
{
	unsigned long	**subkeys;
	char			**keys;

	keys = get_keys(arg);
	subkeys = (unsigned long **)malloc(sizeof(unsigned long *) * 3);
	subkeys[0] = generate_keys(ft_atou_base(keys[0], 16));
	subkeys[1] = generate_keys(ft_atou_base(keys[1], 16));
	subkeys[2] = generate_keys(ft_atou_base(keys[2], 16));
	return (subkeys);
}

unsigned long			modify(t_arg *arg, unsigned long temp,
							unsigned long **subkeys, unsigned long ttmp)
{
	temp = work_blocks(arg, ttmp, subkeys[0]);
	arg->flg->enc_mode ^= 1;
	ttmp = work_blocks(arg, temp, subkeys[1]);
	arg->flg->enc_mode ^= 1;
	temp = work_blocks(arg, ttmp, subkeys[2]);
	return (temp);
}

static unsigned long	*subdes(t_arg *arg, const unsigned long *plain,
								size_t blocks)
{
	unsigned long	**subkeys;
	unsigned long	*temp;
	unsigned long	ttmp;
	size_t			i;
	unsigned long	iv;

	subkeys = keygen(arg);
	temp = (unsigned long *)malloc(sizeof(unsigned long) * (blocks));
	iv = 0;
	(arg->flg->sec_mode == 1) ? iv = ft_atou_base(arg->iv, 16) : 1;
	i = 0;
	while (i < blocks)
	{
		ttmp = plain[i];
		(arg->flg->enc_mode == 1 && arg->flg->sec_mode == 1) ? ttmp ^= iv : 1;
		temp[i] = modify(arg, temp[i], subkeys, ttmp);
		if (arg->flg->enc_mode == 1 && arg->flg->sec_mode == 1)
			iv = temp[i];
		else if (i > 0 && arg->flg->sec_mode == 1)
			iv = plain[i - 1];
		if (arg->flg->enc_mode == 0 && arg->flg->sec_mode == 1)
			temp[i] ^= iv;
		i++;
	}
	return (temp);
}

t_uberstr				*des3(t_arg *arg)
{
	unsigned long	*plain;
	unsigned long	*cyph;
	t_uberstr		*temp;
	unsigned long	i;
	char			*meh;

	temp = handle_input(arg, 48);
	plain = gen_blocks(temp->str, ((temp->size - 1) / 16) + 1);
	cyph = subdes(arg, plain, ((temp->size - 1) / 16) + 1);
	temp = t_uberdup("", 0);
	i = 0;
	while (i < ((arg->str->size - 1) / 8) + 1)
	{
		meh = ft_utoa_base(cyph[i], 16);
		temp->str = ft_strnjoin(temp->str, meh, temp->size, ft_strlen(meh));
		temp->size += ft_strlen(meh);
		i++;
	}
	temp = hex_to_str(temp->str, temp->size);
	return (temp);
}

t_uberstr				*des3cbc(t_arg *arg)
{
	arg->flg->sec_mode = 1;
	return (des3(arg));
}
