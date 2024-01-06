/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:36:17 by sumjo             #+#    #+#             */
/*   Updated: 2023/03/24 19:19:03 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_len(long n)
{
	int	cnt;

	cnt = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		cnt++;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		i;
	long	num;

	num = (long) n;
	i = ft_num_len(num);
	arr = malloc(i + 1);
	if (!arr)
		return (0);
	arr[i] = 0;
	i--;
	if (n < 0)
		num *= -1;
	while (i >= 0)
	{
		arr[i] = "0123456789"[num % 10];
		num /= 10;
		i--;
	}
	if (n < 0)
		arr[0] = '-';
	return (arr);
}
