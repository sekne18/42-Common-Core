/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <jsekne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 09:09:49 by jsekne            #+#    #+#             */
/*   Updated: 2025/08/07 09:09:51 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
 * Monitor routine that checks the state of the philosophers.
 * It runs in a separate thread and continuously checks if any philosopher
 * has died or if all have eaten enough. If either condition is met, it exits.
 * Returns NULL when done.
*/
void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data) || check_all_ate(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}

/*
 * Check if a philosopher has died by comparing the time since their last meal
 * to the time limit for dying. If a philosopher has died, it sets the
 * `someone_died` flag and prints the death message.
 * Returns 1 if a philosopher has died, 0 otherwise.
*/
int	check_death(t_data *data)
{
	int			i;
	long long	current_time;

	i = 0;
	current_time = get_time();
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (current_time - data->philos[i].last_meal_time
			>= (long long)data->time_to_die)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			pthread_mutex_lock(&data->death_mutex);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			print_status(&data->philos[i], DIED);
			return (1);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (0);
}

/* 
 * Check if all philosophers have eaten enough times.
 * If the `must_eat` condition is set, it checks if each philosopher has
 * eaten at least that many times. If all have, it sets the `all_ate_enough`
 * flag and returns 1. Otherwise, it returns 0.
*/
int	check_all_ate(t_data *data)
{
	int	i;
	int	count;

	if (data->must_eat == -1)
		return (0);
	i = 0;
	count = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].meals_eaten >= data->must_eat)
			count++;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	if (count == data->nb_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->all_ate_enough = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}
