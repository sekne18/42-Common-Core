/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:55:24 by jans              #+#    #+#             */
/*   Updated: 2024/10/17 22:25:17 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	radix_sort(t_list **stack_a, t_list **stack_b)
{
	int	max_bits;
	int	size;
	int max_tmp;

	max_bits = find_max_bits(*stack_a);
	max_tmp = max_bits;
	while (max_bits--)
	{
		size = ft_lstsize(*stack_a);
		while (size--)
		{
			// Check is its been solved
			if (get_bit(ft_lstlastnum(*stack_a), (max_tmp - max_bits)))
				ra(stack_a);
			else
				pb(stack_a, stack_b);
		}
		while (*stack_b)
			pa(stack_a,stack_b);
	}
}

int	find_max_bits(t_list *stack_a)
{
	int	max_bits;
	int max_num;

	max_bits = 0;
	max_num = ft_lstmax(stack_a);
	while (max_num)
	{
		max_bits++;
		max_num = max_num >> 1;
	}
	return (max_bits);
}

int	get_bit(int n, int bit_pos)
{
	return ((n >> bit_pos) & 1);
}
