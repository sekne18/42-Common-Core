/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:18:09 by fmol              #+#    #+#             */
/*   Updated: 2024/12/17 13:22:31 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	contains(char const *set, const char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*begin;
	const char	*end;
	char		*res;
	int			i;
	int			flag;

	flag = 0;
	begin = s1;
	end = s1 + ft_strlen(s1) - 1;
	while (contains(set, *begin) && begin < end)
		begin++;
	while (contains(set, *end) && begin < end)
		end--;
	if (!contains(set, *begin))
		flag = 1;
	res = malloc(sizeof(char) * (end - begin + 1 + flag));
	if (!res)
		return (NULL);
	i = -1;
	while (flag && ++i <= end - begin)
		res[i] = *(begin + i);
	if (i < 0)
		i++;
	res[i] = '\0';
	return (res);
}
/*
#include <stdio.h>
int	main()
{
	char *a = "---+++abc++++----  ";
	char *b = " -+";
	char *c = ft_strtrim(a, b);
	printf("%s\n", c);
	printf("%c\n", *(c + 2));
	free(c);
	return (0);
}*/
