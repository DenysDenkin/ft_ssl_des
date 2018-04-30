/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 20:38:24 by ddenkin           #+#    #+#             */
/*   Updated: 2017/10/29 18:50:52 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t size1, size_t size2)
{
	size_t	i;
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	res = (char *)malloc(sizeof(char) * (size1 + size2 + 1));
	if (res == NULL)
		return (NULL);
	while (i < size1)
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < size2)
	{
		res[size1 + i] = s2[i];
		i++;
	}
	res[size1 + size2] = '\0';
	return (res);
}
