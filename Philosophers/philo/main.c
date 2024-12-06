/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:16:45 by jans              #+#    #+#             */
/*   Updated: 2024/12/06 13:12:25 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv, argc == 6);
		if (init_data(&table))
			return (1);
		start_eating(&table);
		clean(&table);
	}
	else
		printf("Wrong input\n");
	return (0);
}
