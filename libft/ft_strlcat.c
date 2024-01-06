/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:41:05 by sumjo             #+#    #+#             */
/*   Updated: 2023/03/24 19:16:21 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d_size;
	size_t	s_size;

	i = 0;
	d_size = ft_strlen(dst);
	s_size = ft_strlen(src);
	if (dst == 0 || src == 0)
		return (0);
	if (dstsize < d_size)
		return (s_size + dstsize);
	while (*dst != 0)
		dst++;
	while (src[i] && i + d_size + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (d_size + s_size);
}
