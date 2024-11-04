/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:43:32 by jans              #+#    #+#             */
/*   Updated: 2024/11/03 13:34:56 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_input(t_table *table, char **argv)
{
	//argv 6 500 200 200 [5]
	table = malloc(t_table);
	if (!table)
		error_exit("Error when malloc");
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[6])
		table->nbr_limit_meals = ft_atol(argv[6]);
}

void	init_data(t_table *table)
{	
	

}
