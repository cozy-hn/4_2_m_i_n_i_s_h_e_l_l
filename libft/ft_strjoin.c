/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:54:32 by jiko              #+#    #+#             */
/*   Updated: 2023/03/17 13:28:30 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	tmp = ft_calloc(s1_len + s2_len + 1, 1);
	if (!tmp)
		return (tmp);
	ft_strlcat(tmp, (char *)s1, s1_len + 1);
	ft_strlcat(tmp, (char *)s2, s1_len + s2_len + 1);
	return (tmp);
}
