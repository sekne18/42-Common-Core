/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:32:31 by jans              #+#    #+#             */
/*   Updated: 2024/12/06 13:13:08 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_eating(t_table *table)
{
	int		i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		pthread_create(&table->philos[0].thread_id, NULL, single_philo_simulation, &table->philos[0]);
	else
	{
		while (++i < table->philo_nbr)
			pthread_create(&table->philos[i].thread_id, NULL, eating_simulation,
				&table->philos[i]);
	}
	table->start_simulation = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	pthread_create(&table->monitor_thread, NULL, monitor, table);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	pthread_join(table->monitor_thread, NULL);
}

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
