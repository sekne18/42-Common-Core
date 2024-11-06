/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:16:45 by jans              #+#    #+#             */
/*   Updated: 2024/11/05 10:17:28 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	printf("%d", argc);
	if (argc >= 5 && argc <= 6)
	{
		// 1) Erros checking, filling table table
		parse_input(&table, argv, argc == 6);

		// 2) Mallocing philosophers, creating the thing
		init_data(&table);

		// 3) Start
		start_eating(&table);

		// 4) No leaks
		//clean(&table);
	}
	else
		error_exit("Wrong input");
	return (0);
}
