/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <jsekne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 09:12:31 by jsekne            #+#    #+#             */
/*   Updated: 2025/08/07 09:12:33 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
