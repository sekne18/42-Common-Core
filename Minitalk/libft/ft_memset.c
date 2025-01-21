/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jan <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:29:42 by jan               #+#    #+#             */
/*   Updated: 2024/10/10 18:45:14 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>

void	*ft_memset(void *s, int c, size_t  n);

int	main()
{
	char	str[] = "This is campus 19!";
 	ft_memset(str, '#', 1);
	printf("%s\n", str);
	return (0);
}
*/
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*new;
	unsigned char	ch;

	new = s;
	ch = c;
	while (n-- > 0)
		*new++ = ch;
	return (s);
}
