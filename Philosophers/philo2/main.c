
#include "philo.h"

int	start_simulation(t_table *table)
{
	int				i;
	pthread_t		monitor_thread;

	table->start_simulation = get_timestamp();
	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].last_meal_time = table->start_simulation;
		if (pthread_create(&table->philos[i].thread_id, NULL,
				philo_life, &table->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, table) != 0)
		return (1);
	i = 0;
	while (i < table->philo_nbr)
		pthread_join(table->philos[i++].thread_id, NULL);
	pthread_join(monitor_thread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (printf("Invalid arguments\n"), 1);
	if (parse_input(&table, argv, argc == 6) != 0)
		return (1);
	if (init_data(&table) != 0)
		return (1);
	if (start_simulation(&table) != 0)
		return (1);
	clean(&table);
	return (0);
}
