/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:35:17 by fmol              #+#    #+#             */
/*   Updated: 2024/10/11 13:39:50 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
char flame(unsigned int x, char y)
{
	return (y + x);
}

#include <stdio.h>
int	main()
{
	char *ptr = "aaaaaaaaaaaaaaa";
	char *x = ft_strmapi(ptr, &flame);
	printf("%s\n", x);
	free(x);	
	return (0);
}*/
