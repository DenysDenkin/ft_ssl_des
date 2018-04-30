/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:33:01 by ddenkin           #+#    #+#             */
/*   Updated: 2018/02/18 18:35:35 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../inc/des_permut.h"

unsigned long			mutate_des(unsigned long key, const int *table,
									int isize, int osize)
{
	unsigned long	res;
	int				i;

	i = 0;
	res = 0;
	while (i < osize)
	{
		res |= (((key >> (isize - table[i])) % 2) << (osize - 1 - i));
		i++;
	}
	return (res);
}

unsigned long			f(unsigned long r, unsigned long k)
{
	unsigned long	res;
	int				i;
	unsigned long	b[8];
	int				s[8];

	res = mutate_des(r, g_ebit, 32, 48);
	res ^= k;
	i = -1;
	while (++i < 8)
	{
		b[i] = res << (16 + i * 6) >> 58;
		s[i] = g_s[i][(b[i] % 2 + (b[i] / 32) * 2) * 16 + (b[i] % 32) / 2];
	}
	i = 0;
	res = 0;
	while (i < 8)
	{
		res = res << 4;
		res |= s[i++];
	}
	res = mutate_des(res, g_p, 32, 32);
	return (res);
}

unsigned long			*generate_keys(unsigned long key)
{
	unsigned long	*subkeys;
	unsigned long	permutkey;
	unsigned long	c[17];
	unsigned long	d[17];
	int				i;

	subkeys = (unsigned long *)malloc(sizeof(unsigned long) * 17);
	permutkey = mutate_des(key, g_pc1, 64, 56);
	c[0] = permutkey >> 28;
	d[0] = (permutkey << 36) >> 36;
	i = 0;
	while (++i < 17)
	{
		c[i] = rotl(c[i - 1], g_shifts[i - 1]);
		d[i] = rotl(d[i - 1], g_shifts[i - 1]);
	}
	i = 0;
	while (++i < 17)
		subkeys[i] = mutate_des(c[i] << 28 | d[i], g_pc2, 56, 48);
	return (subkeys);
}

unsigned long			subkey_magic(t_arg *arg, unsigned long *subkeys,
									unsigned long ip)
{
	unsigned long	l[17];
	unsigned long	r[17];
	int				i;

	l[0] = ip >> 32;
	r[0] = ip << 32 >> 32;
	i = 1;
	while (i < 17)
	{
		l[i] = r[i - 1];
		if (arg->flg->enc_mode == 1)
			r[i] = l[i - 1] ^ f(r[i - 1], subkeys[i]);
		else
			r[i] = l[i - 1] ^ f(r[i - 1], subkeys[17 - i]);
		i++;
	}
	return (r[16] << 32 | l[16]);
}

unsigned long			work_blocks(t_arg *arg, unsigned long plain,
									unsigned long *subkeys)
{
	unsigned long	temp;

	temp = mutate_des(plain, g_ip, 64, 64);
	temp = subkey_magic(arg, subkeys, temp);
	temp = mutate_des(temp, g_ip1, 64, 64);
	return (temp);
}
