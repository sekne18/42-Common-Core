/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <jsekne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 09:10:17 by jsekne            #+#    #+#             */
/*   Updated: 2025/08/07 09:10:18 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	t;
	long long		ms;

	if (gettimeofday(&t, NULL) != 0)
		return (-1);
	ms = (long long)t.tv_sec * 1000;
	ms += t.tv_usec / 1000;
	return (ms);
}

/*
 * Smart sleep function that allows the philosopher to sleep for a specified
 * time while checking if someone has died. It uses a loop to check the
 * `someone_died` flag and sleeps in small increments to avoid busy waiting.
*/
void	smart_sleep(long long time_to_sleep, t_data *data)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time_to_sleep)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_died)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		usleep(500);
	}
}

/*
 * Print the status of the philosopher with a timestamp.
*/
void	print_status(t_philo *philo, t_status status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->write_mutex);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died && status != DIED)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_unlock(&philo->data->write_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	timestamp = get_time() - philo->data->start_time;
	if (status == THINKING)
		printf("%lld %d is thinking\n", timestamp, philo->id);
	else if (status == EATING)
		printf("%lld %d is eating\n", timestamp, philo->id);
	else if (status == SLEEPING)
		printf("%lld %d is sleeping\n", timestamp, philo->id);
	else if (status == TAKE_FORK)
		printf("%lld %d has taken a fork\n", timestamp, philo->id);
	else if (status == DIED)
		printf("%lld %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

int	ft_atoi(const char *str)
{
	int	result;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result);
}

/*
 * Validate the command line arguments.
 * It checks if all arguments are positive integers and within the limits.
 * Returns 1 if valid, 0 otherwise.
*/
int	is_valid_args(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		if (ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	if (ft_atoi(argv[1]) > MAX_PHILOS)
		return (0);
	return (1);
}
