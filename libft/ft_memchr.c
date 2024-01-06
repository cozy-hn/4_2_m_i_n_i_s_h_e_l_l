/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:03:16 by sumjo             #+#    #+#             */
/*   Updated: 2023/03/17 21:36:30 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*a;
	size_t				i;

	a = s;
	i = 0;
	while (i < n)
	{
		if (*a == (unsigned char)c)
			return ((char *)a);
		a++;
		i++;
	}
	if (i < n)
	{
		if ((unsigned char)c == *a)
			return ((char *)a);
	}
	return (0);
}
