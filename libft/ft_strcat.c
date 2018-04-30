/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 17:11:28 by ddenkin           #+#    #+#             */
/*   Updated: 2017/11/05 19:24:48 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t i;
	size_t s1_size;
	size_t s2_size;

	s1_size = 0;
	s2_size = 0;
	while (s1[s1_size] != '\0')
		s1_size++;
	while (s2[s2_size] != '\0')
		s2_size++;
	i = 0;
	while (i < s2_size)
	{
		s1[s1_size + i] = s2[i];
		i++;
	}
	s1[s1_size + s2_size] = '\0';
	return (s1);
}
