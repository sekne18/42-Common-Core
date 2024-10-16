/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:45:14 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/16 22:19:17 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc < 2)
		return (1);
	if (!validate_args(argc, argv, &stack_a))
	{
		ft_putstr_fd("Error\n", 1);
		ft_lstclear(&stack_a);
		return (0);
	}
	radix_sort(&stack_a, &stack_b);
	ft_lstclear(&stack_a);
	return (1);
}
