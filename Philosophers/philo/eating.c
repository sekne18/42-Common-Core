/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:32:31 by jans              #+#    #+#             */
/*   Updated: 2025/01/20 14:58:22 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Creates threads, sets start_sim time and threads state. 
 * Handles clearing the threads and mutexes if it fails during the execution.
 *
 * RETURNS: status and clears all allocated memory/created threads.
 * */
int	start_eating(t_table *table)
{
	int	threads_ready;

	threads_ready = create_threads(table);
	if (threads_ready)
		return (clean(table, threads_ready, false), 1);
	table->start_simulation = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	if (pthread_create(&table->monitor_thread, NULL, monitor, table) != 0)
		return (clean(table, table->philo_nbr, false), 1);
	return (clean(table, table->philo_nbr, true), 0);
}

/*
 * Contains main eating simualtion logic.
 * 1. Waits for all threads to be ready
 * 2. Increments threads_running_nbr (each thread will increment it)
 * 3. Desync philos to avoid dead_locks
 * 4. Execute as long as philos are alive or nbr_limit_meals was reached 
 * */
void	*eating_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_time(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	inc_threads(&philo->table->table_mutex, &philo->table->threads_running_nbr);
	desync_philos(philo);
	while (!sim_done(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

/*
 * Simulates eating.
 * Locks forks, saves last_meal_time and checks for nbr_limit_meals
 * */
void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_status(TAKE_SECOND_FORK, philo);
	set_time(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

/*
 * Executes simulation for a single philosopher.
 * Has a similar logic to eating_simulation function
 * */
void	*single_philo_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_time(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	inc_threads(&philo->table->table_mutex, &philo->table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo);
	while (!sim_done(philo->table))
		usleep(200);
	return (NULL);
}

/*
 * Simulating thinking.
 * Puts philo to thinking state.
 * */
void	thinking(t_philo *philo, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_sim)
		write_status(THINKING, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}
