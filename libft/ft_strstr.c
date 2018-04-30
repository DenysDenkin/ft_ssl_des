/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:45:28 by ddenkin           #+#    #+#             */
/*   Updated: 2017/11/02 17:08:16 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (ft_strcmp(needle, "") == 0)
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		if (needle[k] == '\0')
			break ;
		if (haystack[i + k] != needle[k])
		{
			i++;
			k = 0;
		}
		else
			k++;
	}
	if (haystack[i] == '\0' && needle[k] != '\0')
		return (NULL);
	return (((char *)haystack) + i);
}
