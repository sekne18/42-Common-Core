/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jan <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:17:49 by jan               #+#    #+#             */
/*   Updated: 2024/10/11 22:22:14 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n);

int	main()
{
	char	dest[19];
	char	src[] = "This is campus 19!";
	ft_memmove(((void *)0), ((void *)0), 5);
	printf("%s\n", dest);
	return (0);
}
*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	unsigned int		i;

	if (!dest && !src)
		return (NULL);
	i = -1;
	s = src;
	d = dest;
	if (d > s && d < s + n)
	{
		while (n--)
			d[n] = s[n];
	}
	else
	{
		while (++i < n)
			d[i] = s[i];
	}
	return (dest);
}
