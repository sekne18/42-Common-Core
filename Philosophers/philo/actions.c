/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <jsekne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 09:09:21 by jsekne            #+#    #+#             */
/*   Updated: 2025/08/07 09:09:24 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Take forks for the philosopher. The order of taking forks is determined
 * by the philosopher's ID to avoid deadlock. Odd philosophers take the left
 * fork first, while even philosophers take the right fork first.
 * It locks the mutexes for the forks and prints the status.
*/
void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, TAKE_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, TAKE_FORK);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, TAKE_FORK);
	}
}

/*
 * Simulate eating by the philosopher. It locks the meal mutex to update
 * the last meal time and increments the meals eaten count. It then sleeps
 * for the time it takes to eat.
 * After eating, it prints the status.
*/
void	eat(t_philo *philo)
{
	print_status(philo, EATING);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	smart_sleep(philo->data->time_to_eat, philo->data);
}

/*
 * Drop the forks after eating. It unlocks the mutexes for both forks.
 * This allows other philosophers to take the forks.
*/
void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

/*
 * Simulate sleeping by the philosopher. It prints the sleeping status
 * and sleeps for the specified time to sleep.
 * This allows the philosopher to rest before thinking again.
*/
void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEPING);
	smart_sleep(philo->data->time_to_sleep, philo->data);
}

/*
 * Simulate thinking by the philosopher. It prints the thinking status.
 * If the number of philosophers is even, it sleeps for a short time to
 * allow other philosophers to take their turns.
 * This helps in balancing the simulation and avoiding starvation.
*/
void	think(t_philo *philo)
{
	long long	think_time;

	print_status(philo, THINKING);
	if (philo->data->nb_philos % 2 == 0)
		return ;
	think_time = (philo->data->time_to_eat * 2) - philo->data->time_to_sleep;
	if (think_time < 0)
		think_time = 0;
	smart_sleep(think_time * 0.5, philo->data);
}
