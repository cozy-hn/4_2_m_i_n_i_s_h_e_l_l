/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wlibft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 20:38:09 by jiko              #+#    #+#             */
/*   Updated: 2024/01/09 16:21:04 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*wft_calloc(size_t count, size_t size)
{
	unsigned char	*rtm;

	rtm = malloc(count * size);
	if (!rtm)
		exit(1);
	ft_memset(rtm, 0, count * size);
	return (rtm);
}

// char	*wft_strjoin(char const *s1, char const *s2)
// {
// 	char	*tmp;
// 	int		s1_len;
// 	int		s2_len;

// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	tmp = wft_calloc(s1_len + s2_len + 1, 1);
// 	ft_strlcat(tmp, (char *)s1, s1_len + 1);
// 	ft_strlcat(tmp, (char *)s2, s1_len + s2_len + 1);
// 	return (tmp);
// }

char	*ft_strjoin_char(char const *s1, char const s2)
{
	char	*tmp;
	int		s1_len;

	s1_len = ft_strlen(s1);
	tmp = wft_calloc(s1_len + 2, 1);
	ft_strlcat(tmp, (char *)s1, s1_len + 1);
	tmp[s1_len] = s2;
	free((char *)s1);
	return (tmp);
}

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

char	*wft_strdup(const char *src)
{
	char	*cp;
	char	*tmp;

	cp = wft_calloc(ft_strlen(src) + 1, 1);
	tmp = cp;
	if (tmp != NULL)
	{
		while (*src)
			*tmp++ = *src++;
		return (cp);
	}
	return (NULL);
}

