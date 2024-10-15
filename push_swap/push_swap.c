/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:45:14 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/15 22:01:25 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	write(1, &argv[1][0], 1);
	int	res = ft_atoi("-16234");
	ft_putstr_fd(ft_itoa(res), 1);

	/*
		1) Validate arguments (atoi)
		2) fill stack with the given arguments
		3) 
	*/

	return (1);
}

int	validate_args()
{

}
