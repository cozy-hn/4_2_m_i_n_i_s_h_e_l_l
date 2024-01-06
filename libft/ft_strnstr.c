/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:18:17 by jiko              #+#    #+#             */
/*   Updated: 2023/03/15 17:08:41 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (!(*needle))
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (*(haystack + i))
	{
		j = 0;
		while (*(haystack + i + j) == *(needle + j))
		{
			j++;
			if (i + j > len)
				break ;
			if (!(*(needle + j)))
				return ((char *)(haystack + i));
		}
		i++;
		if (i == len)
			break ;
	}
	return (NULL);
}
