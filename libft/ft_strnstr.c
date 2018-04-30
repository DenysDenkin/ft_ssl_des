/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:01:39 by ddenkin           #+#    #+#             */
/*   Updated: 2017/11/05 19:20:15 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (ft_strcmp(needle, "") == 0)
		return ((char *)haystack);
	while (haystack[i] != '\0' && (i + k) < len)
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
	if ((haystack[i] == '\0' || (i + k) == len) && needle[k] != '\0')
		return (NULL);
	return (((char *)haystack) + i);
}
