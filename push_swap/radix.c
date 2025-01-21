/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:55:24 by jans              #+#    #+#             */
/*   Updated: 2024/11/19 14:08:18 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	radix_sort(t_list **stack_a, t_list **stack_b)
{
	t_list	*head;
	int		size;
	int		max_bits;
	int		j;
	int		i;

	i = -1;
	max_bits = find_max_bits(*stack_a);
	while (i++ < max_bits)
	{
		j = -1;
		size = ft_lstsize(*stack_a);
		while (++j < size && !is_sorted(*stack_a, 1))
		{
			head = *stack_a;
			if (((head->index >> i) & 1) == 1)
				ra(stack_a, 0);
			else
				pb(stack_a, stack_b, 0);
		}
		radix_sort_b(stack_a, stack_b, max_bits, i + 1);
	}
}

void	radix_sort_b(t_list **stack_a, t_list **stack_b, int max_bit, int shift)
{
	t_list	*head;
	int		size;

	size = ft_lstsize(*stack_b);
	while (size-- && shift <= max_bit && !is_sorted(*stack_b, 0))
	{
		head = *stack_b;
		if (((head->index >> shift) & 1) == 1)
			pa(stack_a, stack_b, 0);
		else
			rb(stack_b, 0);
	}
	if (is_sorted(*stack_b, 0) && is_sorted(*stack_a, 1))
		while (*stack_b)
			pa(stack_a, stack_b, 0);
}

int	find_max_bits(t_list *stack_a)
{
	int	max_bits;
	int	max_num;

	max_bits = 0;
	max_num = ft_lstmax_idx(stack_a);
	while (max_num >> max_bits)
		max_bits++;
	return (max_bits);
}
