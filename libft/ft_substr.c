/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:16:08 by sumjo             #+#    #+#             */
/*   Updated: 2023/03/18 15:42:15 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*arr;
	size_t		i;

	i = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) < start)
	{
		arr = ft_strdup("");
		return (arr);
	}
	if (ft_strlen(s + start) >= len)
		arr = malloc(len + 1);
	else
		arr = malloc (ft_strlen(s + start) + 1);
	if (!arr)
		return (0);
	while (s[start] && i < len)
	{
		arr[i] = s[start];
		start++;
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
