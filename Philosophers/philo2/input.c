#include "philo.h"

long	ft_atol(const char *str)
{
	long	n;

	n = 0;
	while (*str >= '0' && *str <= '9')
		n = n * 10 + (*str++ - '0');
	return (n);
}

int	parse_input(t_table *table, char **argv, bool has_limit)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->nbr_limit_meals = -1;
	if (has_limit)
		table->nbr_limit_meals = ft_atol(argv[5]);
	return (0);
}

void	assign_forks(t_philo *philo, t_fork *forks, int pos, int total)
{
	philo->left_fork = &forks[pos];
	philo->right_fork = &forks[(pos + 1) % total];
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &forks[(pos + 1) % total];
		philo->right_fork = &forks[pos];
	}
}

int	init_data(t_table *table)
{
	int	i;

	table->end_simulation = false;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (!table->philos || !table->forks)
		return (1);
	pthread_mutex_init(&table->write_mutex, NULL);
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i].mutex, NULL);
		table->philos[i].id = i + 1;
		table->philos[i].meals_counter = 0;
		table->philos[i].full = false;
		table->philos[i].table = table;
		assign_forks(&table->philos[i], table->forks, i, table->philo_nbr);
		i++;
	}
	return (0);
}