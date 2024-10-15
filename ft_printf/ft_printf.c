/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:55:22 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/10 14:49:51 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		counter;

	counter = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
			print_argument(++s, args, &counter);
		else
			ft_putchar(*s, &counter);
		s++;
	}
	return (counter);
}

void	print_argument(const char *s, va_list args, int *counter)
{
	if (*s == 's')
		ft_putstr((char *)va_arg(args, char *), counter);
	else if (*s == 'i' || *s == 'd')
		ft_putnbr(va_arg(args, int), counter);
	else if (*s == 'c')
		ft_putchar((char)va_arg(args, int), counter);
	else if (*s == 'u')
		ft_putudec((unsigned int)va_arg(args, unsigned int), counter);
	else if (*s == 'p')
		ft_putvoid((void *)va_arg(args, void *), counter);
	else if (*s == 'X' || *s == 'x')
		ft_puthex(*s, (unsigned int)va_arg(args, int), counter);
	else if (*s != 0)
		ft_putchar(*s, counter);
}
