/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:38:11 by sumjo             #+#    #+#             */
/*   Updated: 2023/03/17 21:31:32 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*arr;
	size_t			i;

	i = 0;
	arr = malloc(count * size);
	if (!arr)
		return (0);
	while (i < count * size)
	{
		arr[i] = '\0';
		i++;
	}
	return (arr);
}
