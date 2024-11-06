/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:29:37 by jans              #+#    #+#             */
/*   Updated: 2024/11/05 09:18:52 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLISECOND == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime");
	return (1919);
}

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

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (sim_done(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;

		if (rem / 1e3)
			usleep(usec / 2);
		else
		{
			//spinlock
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}
