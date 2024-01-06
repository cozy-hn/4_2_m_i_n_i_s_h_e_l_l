/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:16:56 by sumjo             #+#    #+#             */
/*   Updated: 2023/03/24 17:16:57 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_compare(const char *a, const char *b, size_t len, size_t i)
{
	size_t		j;
	size_t		size;

	j = 0;
	size = len - i;
	if (size < ft_strlen(a))
		return (0);
	while (a[j] && j < size)
	{
		if (a[j] != b[j])
		{
			return (0);
		}
		j++;
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && i < len)
	{
		if (*needle == *haystack)
		{
			if (ft_compare(needle, haystack, len, i))
				return ((char *)haystack);
		}
		i++;
		haystack++;
	}
	return (0);
}
