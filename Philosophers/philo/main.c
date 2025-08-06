

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo nb_philos time_die time_eat time_sleep "
			"[must_eat]\n");
		return (1);
	}
	if (!is_valid_args(argv, argc))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (init_data(&data, argv, argc))
		return (1);
	if (start_simulation(&data))
	{
		cleanup_mutexes(&data);
		return (1);
	}
	cleanup_mutexes(&data);
	return (0);
}