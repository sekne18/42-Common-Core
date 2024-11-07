/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:46:36 by jans              #+#    #+#             */
/*   Updated: 2024/11/07 17:49:43 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	merge_sort(t_list **stack_a, t_list **stack_b)
{
	int	size;

	size = ft_lstsize(*stack_a);
	if (size <= 150)
		merge_sort_small(stack_a, stack_b);
	else
		merge_sort_big(stack_a, stack_b);
	move_to_stack_a(stack_a, stack_b);
	if (!is_sorted(*stack_a) || *stack_b)
		merge_sort(stack_a, stack_b);
}

void	merge_sort_small(t_list **stack_a, t_list **stack_b)
{
	int	median;
	int	size;

	size = ft_lstsize(*stack_a);
	if (size > 1)
	{
		median = find_median(*stack_a, size);
		while (size--)
		{
			if ((*stack_a)->index < median)
				pb(stack_a, stack_b, 0);
			else
				ra(stack_a, 0);
		}
		merge_sort_small(stack_a, stack_b);
	}
}

void	merge_sort_big(t_list **stack_a, t_list **stack_b)
{
	int	size;
	int quart;

	quart = 0;
	if (orig_size < 4)
	{
		sort_3(stack_a);
		return ;
	}
	find_quartiles(*stack_a, &q1, &q2, &q3);
    while (++quartile <= 4)
    {
        int target_quartile = (quartile == 1) ? q1 : (quartile == 2) ? q2 : (quartile == 3) ? q3 : INT_MAX;
        
        size = ft_lstsize(*stack_a);
        while (size--)
        {
            if ((*stack_a)->index < target_quartile)
            {
                pb(stack_a, stack_b, 0);
                if ((*stack_b)->next && (*stack_b)->index < (*stack_b)->next->index)
                    rb(stack_b, 0);
            }
            else
                ra(stack_a, 0);
        }
    }
}

void	find_quartiles(t_list *stack, int *q1, int *q2, int *q3)
{
	int		*values;
	int		i;
	int		size;
	t_list *current;
	
	size = ft_lstsize(stack);
	current = stack;
	i = 0;
	values = malloc(size * sizeof(int));
	while (current) 
	{
		values[i++] = current->index;
		current = current->next;
	}
	qsort(values, size, sizeof(int), compare_ints);
    *q1 = values[size / 4];
    *q2 = values[size / 2];
    *q3 = values[3 * size / 4];
    free(values);
}

void	move_to_stack_a(t_list **stack_a, t_list **stack_b)
{
	int	max;
	int	size;
	int	steps_to_rot;

	if (!*stack_b)
		return ;
	size = ft_lstsize(*stack_b);
	max = ft_lstmax_idx(*stack_b);
	steps_to_rot = rotate_count(*stack_b, max);
	if (steps_to_rot > size / 2)
		rot_to_pos(size - steps_to_rot, stack_b, &rrb);
	else
		rot_to_pos(steps_to_rot, stack_b, &rb);
	pa(stack_a, stack_b, 0);
	move_to_stack_a(stack_a, stack_b);
}

void	rot_to_pos(int count, t_list **stack_b, void (*op)(t_list **stack_b, int bouns))
{
	while (count--)
		op(stack_b, 0);
}

int	rotate_count(t_list *stack, int index)
{
	int	steps;

	steps = 0;
	while (stack)
	{
		if (stack->index == index)
			return (steps);
		steps++;
		stack = stack->next;
	}
	return (steps);
}
