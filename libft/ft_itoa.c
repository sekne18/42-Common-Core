/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 08:20:09 by jans              #+#    #+#             */
/*   Updated: 2024/10/10 18:56:46 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 
//#include <stdio.h>

char	*ft_itoa(int n);
int		num_len(int n);
void	ft_swap(char *arr, int len);

/*
int	main()
{
	printf("%s\n", ft_itoa(-99956313));
	return (0);
}
*/
char	*ft_itoa(int n)
{
	char	*arr;
	int		i;
	int		is_neg;

	is_neg = 1;
	i = 0;
	arr = malloc((num_len(n) + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	if (n == 0)
		arr[i++] = 0 + '0';
	if (0 > n)
		is_neg = -1;
	while (n != 0)
	{
		arr[i++] = ((n % 10) * is_neg) + '0';
		n /= 10;
	}
	if (is_neg == -1)
		arr[i++] = '-';
	arr[i] = '\0';
	ft_swap(arr, i);
	return (arr);
}

void	ft_swap(char *arr, int len)
{
	int		i;
	char	tmp;

	i = -1;
	while (++i < --len)
	{
		tmp = arr[i];
		arr[i] = arr[len];
		arr[len] = tmp;
	}
}

int	num_len(int n)
{
	int	len;

	len = 0;
	if (0 >= n)
		len++;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}
