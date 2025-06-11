
#include "philo.h"

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long ms)
{
	long	start;

	start = get_timestamp();
	while (get_timestamp() - start < ms)
		usleep(500);
}

void	print_status(t_philo *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->table->write_mutex);
	time = get_timestamp() - philo->table->start_simulation;
	if (!philo->table->end_simulation)
		printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork->mutex);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo->last_meal_time = get_timestamp();
	philo->meals_counter++;
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter >= philo->table->nbr_limit_meals)
		philo->full = true;
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->table->end_simulation && !philo->full)
	{
		eat(philo);
		print_status(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
