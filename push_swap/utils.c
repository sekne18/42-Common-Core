/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:57:06 by jans              #+#    #+#             */
/*   Updated: 2024/11/06 21:34:33 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_median(t_list *stack, int size)
{
	int		*values;
	t_list	*current;
	int		i;
	int		median;

	values = malloc(size * sizeof(int));
	current = stack;
	i = 0;
	while (current)
	{
		values[i++] = current->index;
		current = current->next;
	}
	qsort(values, size, sizeof(int), compare_ints);
	median = values[size / 2];
	free(values);
	return (median);
}

int	compare_ints(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}
