/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:06:56 by jans              #+#    #+#             */
/*   Updated: 2024/12/06 11:44:41 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * To ensure all threads have been created successfully and are ready.
 * RETURNS: treads status.
 * */
bool	all_threads_running(pthread_mutex_t *mutex, long *threads,
		long philo_nbr)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*threads == philo_nbr)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}

/*
 * Increments threads_running_nbr
 * */
void	inc_threads(pthread_mutex_t *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

/*
 * We desync philos to prevent deadlocks.
 *
 * If even philo_nbr:
 * 		even philo gets put so short sleep (delayed)
 * Else odd philo_nbr:
 * 		if odd philo:
 * 			put him to thinking
 * 
 * */
void	desync_philos(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}
