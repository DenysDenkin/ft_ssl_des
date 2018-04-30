/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 14:38:00 by ddenkin           #+#    #+#             */
/*   Updated: 2017/11/03 17:20:57 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	myfreelst(t_list **lst)
{
	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		myfreelst(&((*lst)->next));
		free((*lst)->content);
		(*lst)->content = NULL;
		(*lst) = (*lst)->next;
	}
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*res;
	t_list	*start;
	t_list	*fres;

	if (lst != NULL && f != NULL)
	{
		start = f(lst);
		res = start;
		lst = lst->next;
	}
	else
		return (NULL);
	while (lst != NULL)
	{
		fres = f(lst);
		res->next = ft_lstnew(fres->content, fres->content_size);
		if (res->next == NULL)
		{
			myfreelst(&start);
			break ;
		}
		res = res->next;
		lst = lst->next;
	}
	return (start);
}
