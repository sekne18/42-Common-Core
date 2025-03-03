/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jan <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:22:46 by jan               #+#    #+#             */
/*   Updated: 2024/11/26 10:47:40 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_all(char **arr, int del_arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	if (del_arr)
		free(arr);
	return (1);
}

int	count_word_len(const char *s, char c)
{
	int		len;
	char	*start;

	len = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		start = (char *)s;
		while (*s && *s != c)
			s++;
		if (start < s)
			len++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	*start;
	int		i;

	i = 0;
	arr = malloc((count_word_len(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		start = (char *)s;
		while (*s && *s != c)
			s++;
		if (start < s)
		{
			arr[i++] = ft_substr(start, 0, (s - start));
			if (!arr[i - 1] && free_all(arr, 1))
				return (NULL);
		}
	}
	arr[i] = 0;
	return (arr);
}
