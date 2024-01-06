/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:43:28 by jiko              #+#    #+#             */
/*   Updated: 2023/03/17 13:30:21 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	find_first(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (*(s1 + i))
	{
		if (!is_in(*(s1 + i), (char *)set))
			break ;
		i++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		l;
	int		i;
	char	*tmp;

	l = ft_strlen(s1);
	i = find_first(s1, set);
	while (l - i - 1 > 0)
	{
		if (!is_in(*(s1 + l - 1), (char *)set))
		{
			tmp = ft_calloc(l - i + 1, 1);
			if (!tmp)
				return (NULL);
			break ;
		}
		l--;
	}
	if (l < i + 1)
	{
		tmp = ft_calloc(l - i + 1, 1);
		if (!tmp)
			return (NULL);
	}
	ft_strlcpy(tmp, s1 + i, l - i + 1);
	return (tmp);
}
