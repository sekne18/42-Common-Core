/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 08:48:54 by jsekne            #+#    #+#             */
/*   Updated: 2025/01/20 15:59:39 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return (-1);
	else if (table->philo_nbr == 1)
	{
		if (pthread_create(&table->philos[0].thread_id, NULL,
				single_philo_simulation, &table->philos[0]) != 0)
			return (1);
	}
	else
	{
		while (++i < table->philo_nbr)
		{
			if (pthread_create(&table->philos[i].thread_id, NULL,
					eating_simulation, &table->philos[i]) != 0)
				return (i);
		}
	}
	return (0);
}

/*
 * Joins - "waits", for all threads and marks the end_simulation as true
 * */
void	join_threads(t_table *table, int created_threads,
		bool monitor_created)
{
	int	i;

	i = -1;
	while (++i < created_threads)
		pthread_join(table->philos[i].thread_id, NULL);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	if (monitor_created)
		pthread_join(table->monitor_thread, NULL);
}
