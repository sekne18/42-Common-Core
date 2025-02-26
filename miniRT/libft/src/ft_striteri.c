/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:45:19 by fmol              #+#    #+#             */
/*   Updated: 2024/10/10 15:52:47 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		f(i, (s + i));
		i++;
	}
}
/*
void flame(unsigned int x, char *y)
{
	*y = (*y + x);
}
#include <stdio.h>
int	main()
{
	char	s[] = "aaaaaaaaa";
	ft_striteri(s, &flame);
	printf("%s\n", s);
	return (0);
}*/
