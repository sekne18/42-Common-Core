/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jan <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:44:48 by jan               #+#    #+#             */
/*   Updated: 2024/10/10 15:17:00 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>

size_t	strlcpy(char *dst, const char *src, size_t size);

int	main()
{
	char	dst[10];
	char	src[9] = "Campus19!";
	printf("%i\n", strlcpy(dst, src, 10));
	printf("%s\n", dst);
	return (0);
}
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	cpy_len;

	src_len = 0;
	while (src[src_len])
		src_len++;
	if (size > 0)
	{
		if (src_len >= size)
			cpy_len = (size - 1);
		else
			cpy_len = src_len;
		while (*src && cpy_len-- > 0)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (src_len);
}
