/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:01:32 by jiko              #+#    #+#             */
/*   Updated: 2023/03/23 22:57:35 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*tmp;
	int				slen;
	unsigned char	tmpc;

	tmpc = (unsigned char)c;
	tmp = (char *)s;
	slen = ft_strlen(s);
	if (tmpc == 0)
		return (&tmp[slen]);
	if (slen == 0)
		return ((void *)0);
	while (slen > -1)
	{
		if (tmp[slen] == tmpc)
			return ((tmp + slen));
		slen--;
	}
	return (NULL);
}
