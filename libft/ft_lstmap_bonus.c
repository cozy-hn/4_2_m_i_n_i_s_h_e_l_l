/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:56:11 by sumjo             #+#    #+#             */
/*   Updated: 2023/03/28 16:32:44 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*temp;
	void	*temp_content;

	p = 0;
	if (!lst || !f)
		return (0);
	while (lst)
	{
		temp_content = (f(lst->content));
		temp = ft_lstnew(temp_content);
		if (!temp)
		{
			del(temp_content);
			ft_lstclear(&p, del);
			return (0);
		}
		ft_lstadd_back(&p, temp);
		lst = lst->next;
	}
	return (p);
}
