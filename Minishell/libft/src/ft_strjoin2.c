/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:55:49 by fmol              #+#    #+#             */
/*   Updated: 2024/09/13 17:00:03 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calculate_size(int size, char **strs, char *sep)
{
	int	i;
	int	char_count;

	char_count = 0;
	i = 0;
	while (i < size)
	{
		char_count += ft_strlen(strs[i]);
		i++;
	}
	if (size > 1)
		char_count += (size - 1) * ft_strlen(sep);
	return (char_count);
}

void	fill_string(char *result, size_t size, char **strs, char *sep)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (i < size)
	{
		j = 0;
		while (j < ft_strlen(strs[i]))
		{
			result[k] = strs[i][j];
			k++;
			j++;
		}
		j = 0;
		while (j < ft_strlen(sep) && i != size - 1)
		{
			result[k] = sep[j];
			k++;
			j++;
		}
		i++;
	}
}

char	*ft_strsjoin(size_t size, char **strs, char *sep)
{
	char	*ptr;
	int		char_count;

	char_count = calculate_size(size, strs, sep);
	ptr = malloc((char_count + 1) * sizeof(char));
	if (!ptr)
		return ((char *)0);
	if (size == 0)
		return (ptr);
	fill_string(ptr, size, strs, sep);
	return (ptr);
}
/*
#include <stdio.h>
int	main()
{
	char *ptr[] = {"hello", ",", "how", "are", "you"};
	char *ptr2 = ft_strjoin(5, ptr, " -_- ");
	printf("%s\n", ptr2);
	return (0);
}*/
