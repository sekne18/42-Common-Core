/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 08:25:47 by jans              #+#    #+#             */
/*   Updated: 2024/12/06 12:57:38 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_dead(t_philo *philo)
{
	long elapsed;
	long t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	
	elapsed = gettime(MILLISECOND) - get_time(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3; 
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, &table->threads_running_nbr,
				table->philo_nbr))
		;
	while (!sim_done(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !sim_done(table))
		{
			if (philo_dead(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}
