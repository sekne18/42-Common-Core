/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:22:06 by fmol              #+#    #+#             */
/*   Updated: 2024/12/02 13:22:10 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	calc_decimal(const char *nptr)
{
	double	decimal;
	double	div;

	if (nptr[0] != '0' && (nptr[1] != 'x'))
		return (0);
	nptr += 2;
	decimal = 0;
	div = 10;
	while ((*nptr >= '0' && *nptr <= '9') || (*nptr >= 'a' && *nptr <= 'f'))
	{
		decimal *= 16;
		div *= 10;
		if (*nptr >= '0' && *nptr <= '9')
			decimal += (*nptr - '0');
		else if (*nptr >= 'a' && *nptr <= 'f')
			decimal += (*nptr - 'a' + 10);
		nptr++;
	}
	return (decimal / div);
}

double	ft_atod(const char *nptr)
{
	double	sign;
	double	result;

	sign = 1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result *= 10;
		result += *nptr - '0';
		nptr++;
	}
	if (*nptr == ',')
		result += calc_decimal(nptr + 1);
	return (result * sign);
}
