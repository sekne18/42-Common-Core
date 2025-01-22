/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:52:59 by fmol              #+#    #+#             */
/*   Updated: 2024/10/15 08:34:41 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	len;
	void	*result;

	if (size && nmemb > (size_t)-1 / size)
		return (NULL);
	len = nmemb * size;
	result = malloc(len);
	if (!result)
		return (NULL);
	while (len-- > 0)
		((unsigned char *)result)[len] = 0;
	return (result);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*result;

	len = 0;
	while (s[len])
		len++;
	result = malloc(sizeof(char) * (1 + len));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len-- > 0)
		result[len] = s[len];
	return (result);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*result;

	len = 0;
	while (s[len])
		len++;
	if (len < n)
		return (NULL);
	result = malloc(sizeof(char) * (n + 1));
	if (!result)
		return (NULL);
	result[n] = '\0';
	while (n-- > 0)
		result[n] = s[n];
	return (result);
}

static size_t	min(size_t x, size_t y)
{
	if (x > y)
		return (y);
	return (x);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	i = ft_strlen(s);
	if (i - 1 < start)
		i = 0;
	else if (i)
		i = min(len, ft_strlen(s + start));
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	res[i] = '\0';
	while (i-- > 0)
		res[i] = s[start + i];
	return (res);
}
/*
int main()
{
	char *s = ft_substr("trip", 100 , 1);
	s++;
}*/
