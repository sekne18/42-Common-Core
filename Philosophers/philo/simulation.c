

#include "philo.h"

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