/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wlibft_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:37:19 by jiko              #+#    #+#             */
/*   Updated: 2024/01/26 01:09:45 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		(tmp)->next = new;
	}
}

void	wft_lstadd_back_lst(t_lst **lst, t_lst *new)
{
	t_lst	*tmp;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		(tmp)->next = new;
	}
}

int	wft_lstsize(t_token *lst)
{
	int	cnt;

	cnt = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		cnt += 1;
		lst = lst->next;
	}
	return (cnt);
}

t_token	*wft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_lst	*wft_lstlast_lst(t_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
