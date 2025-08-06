

#include "philo.h"

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