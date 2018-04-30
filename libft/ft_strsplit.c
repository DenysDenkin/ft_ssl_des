/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:48:41 by ddenkin           #+#    #+#             */
/*   Updated: 2017/11/05 19:30:18 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char const *s, char c)
{
	int		res;
	int		i;

	res = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			res++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (res);
}

static int		word_length(char const *s, char c, int i)
{
	int	res;

	res = 0;
	while (s[i] != c)
	{
		res++;
		i++;
	}
	return (res);
}

static char		*put_word(char const *s, char c, int *i, int length)
{
	char	*res;
	int		ii;

	res = (char *)malloc(sizeof(char) * (length + 1));
	if (res == NULL)
		return (NULL);
	ii = 0;
	while (s[(*i)] != c)
	{
		res[ii] = s[(*i)];
		ii++;
		(*i)++;
	}
	res[ii] = '\0';
	return (res);
}

static int		split_in_words(char const *s, char c, char ***res, int words)
{
	int		res_i;
	int		i;
	int		length;

	res_i = -1;
	i = 0;
	while (++res_i < words)
	{
		while (s[i] == c)
			i++;
		length = word_length(s, c, i);
		(*res)[res_i] = put_word(s, c, &i, length);
		if ((*res)[res_i] == NULL)
		{
			i = 0;
			while (i < res_i)
				free((*res)[i++]);
			free((*res));
			return (1);
		}
	}
	(*res)[res_i] = 0;
	return (0);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**res;
	int		words;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	if (res == NULL)
		return (NULL);
	split_in_words(s, c, &res, words);
	return (res);
}
