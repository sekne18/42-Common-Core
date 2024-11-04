/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:32:31 by jans              #+#    #+#             */
/*   Updated: 2024/11/04 16:35:14 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
   1. If no meal ,return ->[0]
   2. if only one philo-> ad hoc function
   3. create all threads, all philos
   4. Create a monitor thread -> death
   5. Synchronize the beggining of the simulation
   5.1. pthread_create-> philo starts running!
   5.2. every philo start simultaneously
   6. JOIN everyone
*/
void	start_eating(t_table *table)
{
	int		i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		; // TOOD
	else
	{
		while (++i < table->philo_nbr)
		{
			pthread_create(&table->philos[i].thread_id, NULL, eating_simulation,
			&table->philos[i]);
		}	
		// Start of simulation

		table->start_simulation = gettime(MILLISECOND);
		// Now all threads are ready
		set_bool(&table->table_mutex, &table->all_threads_ready, true);
		
		//Wait for everyone
		i = -1;
		while (++i < table->philo_nbr)
			pthread_join(&table->philos[i].thread_id, NULL);

		//If we manage to reach this line, all philos are FULL!

		
	}
}

void	*eating_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	//Spinlock
	wait_all_threads(philo->table);
	
	// Set last meal time
	
	while (!sim_done(philo->table))
	{
		//am I full?
		if (philo->full)
			break ;
		// eat
		eat(philo);
		// sleep
		
		// think
		thinking(philo);
	}

	return (NULL);
}

