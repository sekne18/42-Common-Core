/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:55:24 by jans              #+#    #+#             */
/*   Updated: 2024/10/18 18:10:41 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	radix_sort(t_list **stack_a, t_list **stack_b)
{
	normalize(stack_a, ft_lstmin(*stack_a));
	sort_positive(stack_a, stack_b);
}

void	sort_positive(t_list **stack_a, t_list **stack_b)
{
	int	size;
	int	max_bits;
	int max_tmp;
	int	el_pushed;

	el_pushed = 0;
	max_bits = find_max_bits(*stack_a);
	max_tmp = max_bits;
	while (max_bits--)
	{
		size = ft_lstsize(*stack_a);
		if (is_sorted(*stack_a))
			break ;
		while (size--)
		{
			if (get_bit(ft_lstlast_idx(*stack_a), (max_tmp - max_bits)) == 0)
				pb(stack_a, stack_b);
			else
				ra(stack_a);
		}
		while (*stack_b)
		{
			el_pushed--;
			pa(stack_a, stack_b);
		}
	}
}

void	normalize(t_list **stack_a, int min)
{
	t_list	*curr;

	curr = *stack_a;
	while (curr->next)
	{
		curr->index = curr->number - min;
		curr = curr->next;
	}
}

int	find_max_bits(t_list *stack_a)
{
	int	max_bits;
	int max_num;

	max_bits = 0;
	max_num = ft_lstmax_idx(stack_a);
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
