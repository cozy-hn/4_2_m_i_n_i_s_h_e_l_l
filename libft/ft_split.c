/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:18:45 by sumjo             #+#    #+#             */
/*   Updated: 2023/03/19 17:25:50 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*ft_inside(char const *s, char c);
static int	ft_word_num(char const *s, char c, int *n);
static int	ft_word_len(char const *s, char c);
static void	ft_free_split(char **arr, int i);

static void	ft_free_split(char **arr, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		free(arr[j]);
		j++;
	}
	free (arr);
}

static char	*ft_inside(char const *s, char c)
{
	char	*arr;
	int		i;

	i = 0;
	arr = malloc(ft_word_len(s, c) + 1);
	if (!arr)
		return (0);
	while (s[i] && s[i] != c)
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

static int	ft_word_num(char const *s, char c, int *n)
{
	int	i;
	int	cnt;

	*n = 0;
	i = 0;
	cnt = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			cnt++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (cnt);
}

static int	ft_word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (ft_word_num(s, c, &i) + 1));
	if (!arr)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			*(arr + i) = ft_inside(s, c);
			if (*(arr + i) == 0)
			{
				ft_free_split(arr, i);
				return (0);
			}
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	*(arr + i) = (void *)0;
	return (arr);
}
