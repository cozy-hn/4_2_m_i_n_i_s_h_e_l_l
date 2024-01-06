/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:12:27 by sumjo             #+#    #+#             */
/*   Updated: 2023/03/19 14:27:45 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*a1;
	const unsigned char	*a2;
	size_t				i;

	i = 0;
	a1 = s1;
	a2 = s2;
	if (n == 0)
		return (0);
	if (!a1 && !a2)
		return (0);
	while (i < n)
	{
		if (a1[i] != a2[i])
			return (a1[i] - a2[i]);
		i++;
	}
	if (i < n)
		return (a1[i] - a2[i]);
	return (a1[i - 1] - a2[i - 1]);
}
