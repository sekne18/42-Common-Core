/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:32:31 by jans              #+#    #+#             */
/*   Updated: 2024/11/05 10:31:39 by jans             ###   ########.fr       */
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
		; // TODO
	else
	{
		while (++i < table->philo_nbr)
			pthread_create(&table->philos[i].thread_id, NULL, eating_simulation,
				&table->philos[i]);
	}
	table->start_simulation = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	
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
		if (philo->full)
			break ;
		
		eat(philo);
		
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
	
		thinking(philo);
	}

	return (NULL);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_status(TAKE_SECOND_FORK, philo);
	
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);

	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	thinking(t_philo *philo)
{
	write_status(THINKING, philo);
}
