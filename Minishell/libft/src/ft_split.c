/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:52:40 by fmol              #+#    #+#             */
/*   Updated: 2024/10/15 06:34:46 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_strs(char const *s, char c)
{
	size_t	count;
	int		flag;

	flag = 0;
	count = 0;
	while (*s)
	{
		if (!flag && *s != c)
		{
			flag = 1;
			count++;
		}
		if (flag && *s == c)
			flag = 0;
		s++;
	}
	return (count);
}

void	ft_free_split(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static char	*dup_str(const char *s, size_t len)
{
	char	*ptr;

	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}

static int	fill_strs(const char *s, char **strs, size_t count, char c)
{
	const char	*end;
	size_t		i;

	i = 0;
	while (i < count)
	{
		if (*s == c)
			s++;
		else
		{
			end = s;
			while (*end && *end != c)
				end++;
			strs[i] = dup_str(s, end - s);
			if (!strs[i])
			{
				ft_free_split(strs);
				return (0);
			}
			s = ++end;
			i++;
		}
	}
	strs[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	count;

	count = count_strs(s, c);
	strs = ft_calloc(sizeof(char *), (count + 1));
	if (!strs)
		return (NULL);
	if (!fill_strs(s, strs, count, c))
	{
		free(strs);
		return (NULL);
	}
	return (strs);
}
/*
#include <stdio.h>
int	main()
{
	char	*a = "  tripouille  42  ";
	char	b = ' ';
	char **x = ft_split(a, b);
	int i = 0;
	while (x[i])
	{
		printf("%s\n", x[i]);
		free(x[i]);
		i++;
	}
	free(x);
	return (0);
}*/
