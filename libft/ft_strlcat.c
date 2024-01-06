/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:20:08 by jiko              #+#    #+#             */
/*   Updated: 2023/03/23 22:21:09 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	lendest;
	unsigned int	lensrc;

	i = 0;
	lendest = ft_strlen(dst);
	lensrc = ft_strlen(src);
	while ((size > lendest + i + 1) && *(src + i))
	{
		*(dst + lendest + i) = *(src + i);
		i++;
	}
	*(dst + lendest + i) = '\0';
	if (size <= ft_strlen(dst))
		return (lensrc + size);
	else
		return (lendest + lensrc);
}
