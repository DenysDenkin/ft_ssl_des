/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddtail.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:31:05 by ddenkin           #+#    #+#             */
/*   Updated: 2017/11/05 19:31:05 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddtail(t_list **alst, t_list *new)
{
	t_list *temp;

	if (alst == NULL || *alst == NULL)
		return ;
	temp = *alst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}
