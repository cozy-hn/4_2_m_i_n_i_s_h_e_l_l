/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:31:06 by sumjo             #+#    #+#             */
/*   Updated: 2023/03/19 14:00:58 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	inside(char *arr, char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		arr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		arr[i] = s2[j];
		i++;
		j++;
	}
	arr[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*arr;
	size_t		len;

	if (!(s1 && s2))
	{
		arr = malloc(1);
		*arr = 0;
		return (arr);
	}
	len = ft_strlen(s1) + ft_strlen(s2);
	arr = malloc(len + 1);
	if (!(arr))
		return (0);
	inside(arr, s1, s2);
	return (arr);
}
