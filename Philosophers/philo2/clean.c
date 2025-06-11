#include "philo.h"

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
}

void	clean(t_table *table)
{
	int	i;

	join_threads(table);
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&table->write_mutex);
	free(table->forks);
	free(table->philos);
}

