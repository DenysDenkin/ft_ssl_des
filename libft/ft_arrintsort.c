/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrintsort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:54:58 by ddenkin           #+#    #+#             */
/*   Updated: 2017/11/01 18:31:45 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrintsort(int **arr, size_t size, int (*comp)(int, int))
{
	size_t	i;
	size_t	j;

	if (arr == NULL || *arr == NULL || comp == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (comp((*arr)[j], (*arr)[j + 1]) < 0)
				ft_swap(&(*arr)[j], &(*arr)[j + 1]);
			j++;
		}
		i++;
	}
}
