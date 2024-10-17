/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:50:00 by jans              #+#    #+#             */
/*   Updated: 2024/10/17 21:16:32 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <limits.h>

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%d", lst->number);
		if (lst->next)
			printf(" -> ");
		lst = lst->next;
	}
	printf("\n");
}

int	ft_lstmax(t_list *stack)
{
	int	max;

	max = INT_MIN;
	if (!stack)
		return (max);
	while (stack->next)
	{
		if (max < stack->number)
			max = stack->number;
		stack = stack->next;
	}
	return (max);
}

int	ft_lstlastnum(t_list *stack)
{
	int	last;

	if (!stack)
		return (0);
	while (stack->next)
		stack = stack->next;
	last = stack->number;
	return (last);
}
