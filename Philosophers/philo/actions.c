

#include "philo.h"

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

void	eat(t_philo *philo)
{
	print_status(philo, EATING);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	smart_sleep(philo->data->time_to_eat, philo->data);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEPING);
	smart_sleep(philo->data->time_to_sleep, philo->data);
}

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