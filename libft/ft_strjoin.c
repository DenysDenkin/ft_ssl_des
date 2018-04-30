/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 20:38:24 by ddenkin           #+#    #+#             */
/*   Updated: 2017/10/29 18:50:52 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	int		i;
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = 0;
	i = -1;
	while (s1[++i] != '\0')
		size++;
	i = -1;
	while (s2[++i] != '\0')
		size++;
	i = -1;
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (res == NULL)
		return (NULL);
	while (s1[++i] != '\0')
		res[i] = s1[i];
	size = i;
	i = -1;
	while (s2[++i] != '\0')
		res[size + i] = s2[i];
	res[size + i] = '\0';
	return (res);
}
