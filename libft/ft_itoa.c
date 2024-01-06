/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:37:35 by jiko              #+#    #+#             */
/*   Updated: 2023/03/17 14:22:21 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_int_len(long long tmp)
{
	int	rtn;

	rtn = 1;
	while (tmp / 10)
	{
		rtn += 1;
		tmp /= 10;
	}
	return (rtn);
}

static char	*al(long long tmp)
{
	char		*rtn;
	int			int_len;
	int			sign;

	sign = 0;
	int_len = get_int_len(tmp);
	if (tmp < 0)
	{
		sign = 1;
		int_len += 1;
		tmp *= -1;
	}
	rtn = ft_calloc(int_len + 1, 1);
	if (!rtn)
		return (NULL);
	while (int_len)
	{
		rtn[int_len - 1] = "0123456789"[tmp % 10];
		tmp /= 10;
		int_len--;
	}
	if (sign)
		rtn[0] = '-';
	return (rtn);
}

char	*ft_itoa(int n)
{
	long long	tmp;
	char		*rtn;

	tmp = (long long)n;
	rtn = al(tmp);
	return (rtn);
}
