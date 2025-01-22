/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:03:10 by fmol              #+#    #+#             */
/*   Updated: 2024/10/14 16:14:13 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

static int	get_len(int n)
{
	int	i;

	i = 0;
	if (n == INT_MIN)
	{
		i++;
		n /= 10;
	}
	if (n < 0)
		n = -n;
	else if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		len;
	int		sign;

	len = get_len(n);
	sign = 0;
	if (n < 0)
		sign = 1;
	ptr = malloc(sizeof(char) * (len + 1 + sign));
	if (!ptr)
		return (NULL);
	ptr[len + sign] = '\0';
	if (sign)
		ptr[0] = '-';
	while (--len >= 0)
	{
		ptr[len + sign] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	return (ptr);
}
/*
#include <stdio.h>
int	main()
{
	int n = 0;
	char *x = ft_itoa(n);
	printf("%s\n", x);
	free(x);
	return (0);
}*/
