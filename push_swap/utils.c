/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:57:06 by jans              #+#    #+#             */
/*   Updated: 2024/11/19 15:13:47 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_too_big_gap(int fst, int sec)
{
	if (fst > sec)
		return ((fst - sec) > 1);
	else
		return ((sec - fst) > 1);
}

int	compare_ints(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
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

int	next_to_be_moved(t_list *stack)
{
	int	moving;

	moving = ft_lstmax_idx(stack);
	if ((moving - stack->index) == 1)
		return (1);
	return (0);
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
