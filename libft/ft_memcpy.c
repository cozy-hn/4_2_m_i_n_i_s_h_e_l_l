/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:01:38 by jiko              #+#    #+#             */
/*   Updated: 2023/03/15 17:23:38 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*tmp2;

	if (!dst && !src)
		return (NULL);
	tmp = (unsigned char *)dst;
	tmp2 = (unsigned char *)src;
	while (n--)
		*(tmp++) = *(tmp2++);
	return (dst);
}
