/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:43:32 by jans              #+#    #+#             */
/*   Updated: 2024/11/05 12:48:20 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_input(t_table *table, char **argv, int opt)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->nbr_limit_meals = -1;
	if (opt)
		table->nbr_limit_meals = ft_atol(argv[6]);	
}

void	init_data(t_table *table)
{	
	int		i;

	i = -1;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		error_exit("Error when malloc philosopher");
	pthread_mutex_init(&table->table_mutex, NULL);
	pthread_mutex_init(&table->write_mutex, NULL);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (!table->forks)
		error_exit("Error when malloc forks");	
	while (++i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}

void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		pthread_mutex_init(&philo->philo_mutex, NULL);
		assign_forks(philo, table->forks, i);
	}
}

void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(philo_pos + 1) % philo_nbr];
	philo->second_fork = &forks[philo_pos]; 
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_nbr]; 
	}
}


