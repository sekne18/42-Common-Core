/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:26:18 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/14 08:40:40 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdint.h>

int		ft_printf(const char *s, ...);
void	ft_putnbr(int nb, int *counter);
void	ft_putstr(char *str, int *counter);
void	ft_putchar(char c, int *counter);
void	ft_putvoid(void *p, int *counter);
void	ft_puthex(char c, unsigned int n, int *counter);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_putudec(unsigned int nb, int *counter);
void	get_base(char c, char *base);
void	print_argument(const char *s, va_list args, int *counter);
#endif
