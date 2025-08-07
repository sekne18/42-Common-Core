/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <jsekne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 09:10:03 by jsekne            #+#    #+#             */
/*   Updated: 2025/08/07 09:10:05 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
 * Create threads for each philosopher and the monitor.
 * If there is only one philosopher, it creates a single thread for that
 * philosopher. Otherwise, it creates a thread for each philosopher.
 * Returns 0 on success, 1 on failure.
*/
static int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	if (data->nb_philos == 1)
	{
		if (pthread_create(&data->philos[0].thread_id, NULL,
				single_philo_routine, &data->philos[0]))
			return (1);
	}
	else
	{
		while (i < data->nb_philos)
		{
			if (pthread_create(&data->philos[i].thread_id, NULL,
					philosopher_routine, &data->philos[i]))
				return (1);
			i++;
		}
	}
	return (0);
}

/*
 * Join all philosopher threads after the simulation is complete.
*/
static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

/*
 * Start the simulation by creating the necessary threads for philosophers
 * and the monitor. This function handles both the single philosopher case
 * and the multiple philosophers case.
 */
int	start_simulation(t_data *data)
{
	pthread_t	monitor;

	if (data->must_eat == 0)
		return (0);
	if (create_threads(data))
		return (1);
	if (pthread_create(&monitor, NULL, monitor_routine, data))
		return (1);
	pthread_join(monitor, NULL);
	join_threads(data);
	return (0);
}

/*
 * Philosopher routine where each philosopher tries to take forks,
 * eat, sleep, and think in a loop until a condition is met (like death or
 * all philosophers have eaten enough).
*/
void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = philo->data->start_time;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (philo->id % 2 == 0)
		usleep(15000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died || philo->data->all_ate_enough)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}

/*
 * Single philosopher routine for the case where there is only one philosopher.
 * The philosopher takes a fork, simulates eating by sleeping for the time
 * it would take to die, and then exits.
*/
void	*single_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = philo->data->start_time;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_status(philo, TAKE_FORK);
	smart_sleep(philo->data->time_to_die, philo->data);
	return (NULL);
}
