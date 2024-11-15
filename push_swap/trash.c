/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:33:41 by jans              #+#    #+#             */
/*   Updated: 2024/11/15 14:10:02 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

/*void	move_to_stack_a(t_list **stack_a, t_list **stack_b, int *rot_c)
{
	int	max_steps;
	int	min_steps;
	int	steps_to_rot;

	if (!*stack_b)
		return ;
	max_steps = rotate_count(*stack_b, ft_lstmax_idx(*stack_b));
	min_steps = rotate_count(*stack_b, ft_lstmin(*stack_b));
	if (min_steps > max_steps)
		steps_to_rot = max_steps;
	else
		steps_to_rot = min_steps;
	if (steps_to_rot > ft_lstsize(*stack_b) / 2)
		rot_to_pos_b(ft_lstsize(*stack_b) - steps_to_rot, stack_a, stack_b, &rrb);
	else
		rot_to_pos_b(steps_to_rot, stack_a, stack_b, &rb);
	pa(stack_a, stack_b, 0);
	check_for_swap(stack_a);

	if (min_steps < max_steps)
	{
		max_steps = rotate_count(*stack_b, ft_lstmax_idx(*stack_b));
		min_steps = rotate_count(*stack_b, ft_lstmin(*stack_b));
		if (min_steps > max_steps)
			steps_to_rot = max_steps;
		else
			steps_to_rot = min_steps;
		if (steps_to_rot < ft_lstsize(*stack_b) / 2)
			rr(stack_a, stack_b, 0);
		else
			ra(stack_a, 0);
		(*rot_c)++;
	}
	move_to_stack_a(stack_a, stack_b, rot_c);
}*/

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%d (%d)", lst->number, lst->index);
		if (lst->next)
			printf(" -> ");
		lst = lst->next;
	}
	printf("\n");
}

void	find_quartiles(t_list *stack, int *q1, int *q2, int *q3)
{
	int		*values;
	int		i;
	int		size;
	t_list	*current;

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
