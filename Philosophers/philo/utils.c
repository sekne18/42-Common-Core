/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:29:37 by jans              #+#    #+#             */
/*   Updated: 2024/11/03 13:45:21 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

long	ft_atol(const char *nptr)
{
	long	sum;

	sum = 0;
	if (!(*nptr >= '0' && *nptr <= '9'))
		error_exit("Wrong input");
	while (*nptr >= '0' && *nptr <= '9')
		sum = (sum * 10) + (*nptr++ - '0');
	return (sum);
}
