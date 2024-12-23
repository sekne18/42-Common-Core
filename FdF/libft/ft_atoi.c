/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jan <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:47:19 by jan               #+#    #+#             */
/*   Updated: 2024/10/10 18:28:07 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	sum;
	int	is_neg;

	is_neg = 1;
	sum = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			is_neg *= -1;
	while (*nptr >= '0' && *nptr <= '9')
		sum = (sum * 10) + (*nptr++ - '0');
	return (sum * is_neg);
}
