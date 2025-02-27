/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:35:39 by fmol              #+#    #+#             */
/*   Updated: 2024/10/11 10:11:50 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s || !(*s))
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (!size)
		return (len);
	while (i < size && i <= len)
	{
		if (i == size - 1)
		{
			dst[i] = '\0';
			break ;
		}
		dst[i] = src[i];
		i++;
	}
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (dst[len])
		len++;
	if (len >= size)
		return (size + ft_strlen(src));
	if (!size)
		return (len + ft_strlen(src));
	i = 0;
	while (len + i < size)
	{
		if (len + i == size - 1 || !src[i])
		{
			dst[len + i] = '\0';
			break ;
		}
		dst[len + i] = src[i];
		i++;
	}
	while (src[i])
		i++;
	return (len + i);
}

void	ft_bzero(void *s, size_t n)
{
	while (n)
	{
		*(unsigned char *)s = 0;
		s++;
		n--;
	}
}
/*
int	main()
{
	char dest[30];
	for (int i = 0; i < 30; i++)
	{
		dest[i] = 0;
		if (i < 5)
			dest[i] = 'C';
	}
	char * src = (char *)"AAAAAAAAA";
	ft_strlcat(dest, src, -1);
}*/
