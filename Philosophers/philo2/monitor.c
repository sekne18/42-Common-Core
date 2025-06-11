#include "philo.h"

void	*monitor(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!table->end_simulation)
	{
		i = 0;
		while (i < table->philo_nbr && !table->end_simulation)
		{
			if (!table->philos[i].full
				&& get_timestamp() - table->philos[i].last_meal_time
				> table->time_to_die)
			{
				table->end_simulation = true;
				print_status(&table->philos[i], "died");
				break ;
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}