/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jan <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:34:11 by jan               #+#    #+#             */
/*   Updated: 2024/10/10 15:03:49 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>

void *ft_memchr(const void *s, int c, size_t n);

int	main()
{
	char str[] = {0,1,2,3,4,5};
	unsigned char *s = (unsigned char *)ft_memchr(str, 0, 1);
	printf("%s\n", s);
	return (0);
}*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;

	str = s;
	while (n-- > 0)
	{
		if (*str == (unsigned char)c)
			return ((void *)str);
		str++;
	}
	return (0);
}
