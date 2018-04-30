/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:33:56 by ddenkin           #+#    #+#             */
/*   Updated: 2018/02/18 20:25:42 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../inc/ft_comm.h"

int					parse_flg(char **argv, int *i, t_arg *arg)
{
	if (ft_strcmp(argv[(*i)], "-e") == 0)
		arg->flg->enc_mode = 1;
	else if (ft_strcmp(argv[(*i)], "-d") == 0)
		arg->flg->enc_mode = 0;
	else if (ft_strcmp(argv[(*i)], "-i") == 0 && argv[*i + 1][0] != '-')
	{
		arg->flg->i = 1;
		arg->inname = argv[(*i)++ + 1];
	}
	else if (ft_strcmp(argv[(*i)], "-o") == 0 && argv[*i + 1][0] != '-')
	{
		arg->flg->o = 1;
		arg->outname = argv[(*i)++ + 1];
	}
	else if (ft_strcmp(argv[(*i)], "-a") == 0)
		arg->flg->a = 1;
	else
		return (1);
	return (0);
}

void				parse_flags(int argc, char **argv, t_arg *arg)
{
	int		i;

	i = 1;
	arg->comm = argv[0];
	while (i < argc)
	{
		if (parse_flg(argv, &i, arg) == 0)
			;
		else if (ft_strcmp(argv[i], "-k") == 0 && argv[i + 1][0] != '-')
			arg->key = argv[i++ + 1];
		else if (ft_strcmp(argv[i], "-v") == 0 && argv[i + 1][0] != '-')
			arg->iv = argv[i++ + 1];
		i++;
	}
}

static t_uberstr	*filter_pad(t_uberstr *str)
{
	size_t		i;
	int			j;

	i = str->size;
	if (i == 0)
		return (str);
	if (str->str[i - 1] < 9)
	{
		j = 0;
		while (j < str->str[i - 1] && str->str[i - 1 - j] == str->str[i - 1])
			j++;
		if (j != str->str[i - 1])
			return (str);
		while (j > 0)
		{
			str->str[i - j] = 0;
			j--;
			str->size--;
		}
	}
	return (str);
}

int					do_op(t_arg *arg)
{
	int		i;

	i = 0;
	while (ft_strcmp(g_commtab[i].comm, arg->comm) != 0 &&\
			ft_strcmp(g_commtab[i].comm, "") != 0)
		i++;
	if (arg->flg->a == 1 && arg->flg->enc_mode == 0)
		arg->str = base64(arg);
	if ((arg->str = g_commtab[i].func(arg)) == NULL)
		return (-4);
	if (arg->flg->a == 1 && arg->flg->enc_mode == 1)
		arg->str = base64(arg);
	if (arg->flg->enc_mode == 0)
		filter_pad(arg->str);
	write(arg->outfd, arg->str->str, arg->str->size);
	if (arg->flg->enc_mode == 1 && (g_commtab[i].func == base64 ||\
			arg->flg->a == 1))
		write(arg->outfd, "\n", 1);
	return (0);
}

int					main(int argc, char **argv)
{
	t_arg	*arg;

	if (argc < 2)
		return (-1);
	arg = init_arg();
	parse_flags(argc - 1, argv + 1, arg);
	if (arg->flg->i == 1 && (arg->infd = open(arg->inname, O_RDONLY)) == -1)
		return (-2);
	if (arg->flg->o == 1 && (arg->outfd = \
			open(arg->outname, O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1)
		return (-3);
	return (do_op(arg));
}
