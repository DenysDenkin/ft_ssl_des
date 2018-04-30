/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:33:49 by ddenkin           #+#    #+#             */
/*   Updated: 2018/02/18 18:36:29 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/libft.h"
# include <fcntl.h>

typedef struct	s_uberstr
{
	char		*str;
	size_t		size;
}				t_uberstr;

typedef struct	s_flags
{
	int		enc_mode;
	int		sec_mode;
	int		i;
	int		o;
	int		a;
}				t_flags;

typedef struct	s_arg
{
	t_flags		*flg;
	char		*inname;
	char		*outname;
	int			infd;
	int			outfd;
	t_uberstr	*str;
	char		*key;
	char		*iv;
	char		*comm;
}				t_arg;

typedef struct	s_comm
{
	char		*comm;
	t_uberstr	*(*func)(t_arg *arg);
}				t_comm;

t_uberstr		*usage(t_arg *arg);
t_uberstr		*base64(t_arg *arg);
t_uberstr		*des(t_arg *arg);
t_uberstr		*descbc(t_arg *arg);
t_uberstr		*des3(t_arg *arg);
t_uberstr		*des3cbc(t_arg *arg);

t_uberstr		*hex_to_str(const char *hex, size_t size);
unsigned long	work_blocks(t_arg *arg, unsigned long plain, \
					unsigned long *subkeys);
t_uberstr		*pad_str(t_arg *arg);
unsigned long	*gen_blocks(char *str, size_t blocks);
unsigned long	*generate_keys(unsigned long key);
unsigned long	mutate_des(unsigned long key, const int *table, \
				int isize, int osize);
unsigned long	subkey_magic(t_arg *arg, unsigned long *subkeys, \
				unsigned long ip);
t_uberstr		*str_to_hex(const char *str, size_t size);
t_arg			*init_arg();
size_t			ft_strlenn(const char *str, size_t size);
void			count_stuff(int *asize, t_uberstr *res, t_arg *arg);
t_uberstr		*t_uberdup(char *str, size_t size);
unsigned long	rotl(unsigned long value, int shift);
void			input_arg(char *message, char **str, t_arg *arg, size_t size);
t_uberstr		*input_str(t_arg *arg);
t_uberstr		*handle_input(t_arg *arg, size_t keysize);
char			**get_keys(t_arg *arg);
#endif
