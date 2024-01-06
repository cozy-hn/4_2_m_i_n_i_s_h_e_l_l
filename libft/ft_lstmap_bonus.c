/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:12:43 by jiko              #+#    #+#             */
/*   Updated: 2023/03/20 22:41:55 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*dobi_free(void *dobi, void (*del)(void *))
{
	(*del)(dobi);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rtn;
	t_list	*tmp;
	void	*dobi;

	if (!lst)
		return (NULL);
	dobi = (*f)(lst->content);
	rtn = ft_lstnew(dobi);
	if (!rtn)
		return (dobi_free(dobi, del));
	tmp = rtn;
	while (lst->next)
	{
		dobi = (*f)(lst->next->content);
		tmp->next = ft_lstnew(dobi);
		if (!(tmp->next))
		{
			ft_lstclear(&rtn, del);
			return (dobi_free(dobi, del));
		}
		lst = lst->next;
		tmp = tmp->next;
	}
	return (rtn);
}
