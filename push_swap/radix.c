/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:55:24 by jans              #+#    #+#             */
/*   Updated: 2024/10/18 14:23:50 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	radix_sort(t_list **stack_a, t_list **stack_b)
{
	normalize(stack_a, stack_b, ft_lstsize(*stack_a));
	sort_positive(stack_a, stack_b);
	sort_negative(stack_a, stack_b);
	merge_stacks(stack_a, stack_b);
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
			if (get_bit(ft_lstlastnum(*stack_a), (max_tmp - max_bits)) == 0)
			{
				el_pushed++;
				pb(stack_a, stack_b);
			}
			else
				ra(stack_a);
		}
		while (*stack_b && el_pushed)
		{
			el_pushed--;
			pa(stack_a, stack_b);
		}
	}
}

void	sort_negative(t_list **stack_a, t_list **stack_b)
{
	int	size;
	int	max_bits;
	int max_tmp;
	int	el_pushed;

	max_bits = find_max_bits(*stack_a);
	max_tmp = max_bits;
	el_pushed = 0;
	while (max_bits--)
	{
		size = ft_lstsize(*stack_a);
		if (is_sorted(*stack_b))
			break ;
		while (size--)
		{
			if (get_bit(ft_lstlastnum(*stack_b), (max_tmp - max_bits)))
			{
				el_pushed++;
				pa(stack_a, stack_b);
			}
			else
				rb(stack_b);
		}
		while (*stack_a && el_pushed)
		{
			el_pushed--;
			pb(stack_a, stack_b);
		}
	}
}

void	merge_stacks(t_list **stack_a, t_list **stack_b)
{
	t_list	*last;

	while (*stack_b)
	{
		last = *stack_b;
		while (last->next)
			last = last->next;
		last->number = last->number * -1;
		pa(stack_a, stack_b);
	}
}

void	normalize(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*curr;

	if (size == 0)
		return ;
	curr = *stack_a;
	while (curr->next)
		curr = curr->next;	
	if (curr->number < 0)
	{
			curr->number = curr->number * -1;
			pb(stack_a, stack_b);
	}
	else
			ra(stack_a);
	normalize(stack_a, stack_b, --size);
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
