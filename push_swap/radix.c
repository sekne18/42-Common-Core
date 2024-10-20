/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:55:24 by jans              #+#    #+#             */
/*   Updated: 2024/10/20 09:37:50 by jans             ###   ########.fr       */
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
	size = ft_lstsize(*stack_a);
	while (i++ < max_bits)
	{
		j = 0;
		while (j++ < size)
		{
			head = *stack_a;
			if (((head->index >> i) & 1) == 1)
				ra(stack_a);
			else
				pb(stack_a, stack_b);
		}
		while (*stack_b)
			pa(stack_a, stack_b);
	}
}

void	compress_numbers(t_list **stack_a, int len)
{
	t_list	*curr;
	int		min;
	int		i;

	i = 0;
	while (len--)
	{
		min = ft_lst_nextmin(*stack_a);
		curr = *stack_a;
		while (curr)
		{
			if (curr->number == min)
			{
				curr->index = i++;
				break ;
			}
			curr = curr->next;
		}
	}
}

int	find_max_bits(t_list *stack_a)
{
	int	max_bits;
	int max_num;

	max_bits = 0;
	max_num = ft_lstmax_idx(stack_a);
	while (max_num >> max_bits)
		max_bits++;
	return (max_bits);
}
