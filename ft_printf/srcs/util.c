/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 07:20:20 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/17 07:36:35 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *str, int *counter)
{
	int	i;

	if (!str)
	{
		ft_putstr("(null)", counter);
		return ;
	}
	i = -1;
	while (str[++i])
		ft_putchar(str[i], counter);
}

void	ft_putchar(char c, int *counter)
{
	(*counter)++;
	write(1, &c, 1);
}

void	ft_putnbr(int nb, int *counter)
{
	char	res[12];
	int		i;
	int		is_neg;

	i = 0;
	is_neg = 0;
	if (nb == 0)
		res[i++] = '0';
	if (nb < 0)
		is_neg = 1;
	while (nb != 0)
	{
		if (is_neg)
			res[i++] = ((nb % 10) * -1) + '0';
		else
			res[i++] = (nb % 10) + '0';
		nb /= 10;
	}
	if (is_neg)
		res[i++] = '-';
	while (i > 0)
		ft_putchar(res[--i], counter);
}

void	ft_putudec(unsigned int nb, int *counter)
{
	char	res[11];
	int		i;
	int		is_neg;

	i = 0;
	is_neg = 0;
	if (nb == 0)
		res[i++] = '0';
	if (nb < 0)
		is_neg = 1;
	while (nb != 0)
	{
		if (is_neg)
			res[i++] = ((nb % 10) * -1) + '0';
		else
			res[i++] = (nb % 10) + '0';
		nb /= 10;
	}
	if (is_neg)
		res[i++] = '-';
	while (i > 0)
		ft_putchar(res[--i], counter);
}
