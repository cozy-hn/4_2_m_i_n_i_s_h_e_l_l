/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:13:48 by jiko              #+#    #+#             */
/*   Updated: 2023/03/25 13:41:37 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*alloc_zero(void)
{
	char	*tmp;

	tmp = ft_calloc(1, 1);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static char	*al(char const *s, unsigned int st, size_t len, unsigned int *strl)
{
	char	*tmp;
	int		idx;

	idx = 0;
	if (st >= *strl || !len)
		return (alloc_zero());
	else
	{
		if (*strl > st + len)
		{
			tmp = ft_calloc(len + 1, 1);
			if (!tmp)
				return (NULL);
			while (len--)
				tmp[idx++] = s[st++];
		}
		else
			tmp = (char *)ft_strdup(((char *)s + st));
	}
	return (tmp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*tmp;
	unsigned int	strl;

	strl = (unsigned int)ft_strlen(s);
	tmp = al(s, start, len, &strl);
	return (tmp);
}
