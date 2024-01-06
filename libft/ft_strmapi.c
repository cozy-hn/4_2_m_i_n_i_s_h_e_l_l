/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:28:35 by jiko              #+#    #+#             */
/*   Updated: 2023/03/23 22:53:57 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*rtn;
	int		len;

	len = ft_strlen(s);
	rtn = ft_calloc(len + 1, 1);
	if (!rtn)
		return (NULL);
	while (len)
	{
		rtn[len - 1] = (*f)(len - 1, s[len - 1]);
		len--;
	}
	return (rtn);
}
