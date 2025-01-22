/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:45:10 by fmol              #+#    #+#             */
/*   Updated: 2025/01/15 12:56:22 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr_fd(const char *s, size_t n, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	if (len < n)
		n = len;
	write(fd, s, n);
}

void	ft_putnendl_fd(const char *s, size_t n, int fd)
{
	ft_putnstr_fd(s, n, fd);
	ft_putchar_fd('\n', fd);
}
