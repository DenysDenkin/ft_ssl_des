/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:33:44 by ddenkin           #+#    #+#             */
/*   Updated: 2018/02/18 18:33:49 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMM_H
# define FT_COMM_H

t_comm	g_commtab[] =
{
	{"des", des},
	{"des-ecb", des},
	{"des-cbc", descbc},
	{"base64", base64},
	{"des3", des3cbc},
	{"des3-ecb", des3},
	{"des3-cbc", des3cbc},
	{"", usage}
};
#endif
