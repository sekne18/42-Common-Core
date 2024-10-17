/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:28:12 by jans              #+#    #+#             */
/*   Updated: 2024/10/17 21:36:24 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_list **stack_a)
{
	t_list	*curr;
	int		tmp;

	ft_putstr_fd("sa\n", 1);
	curr = *stack_a;
	if (!curr || !curr->next)
		return ;
	while (curr->next)
	{
		if (!curr->next->next)
		{
			tmp = curr->number;
			curr->number = curr->next->number;
			curr->next->number = tmp;
		}
		curr = curr->next;
	}
}

void	sb(t_list **stack_b)
{
	t_list	*curr;
	int		tmp;

	ft_putstr_fd("sb\n", 1);
	curr = *stack_b;
	if (!curr || !curr->next)
		return ;
	while (curr->next)
	{
		if (!curr->next->next)
		{
			tmp = curr->number;
			curr->number = curr->next->number;
			curr->next->number = tmp;
		}
		curr = curr->next;
	}
}

void	ss(t_list **stack_a, t_list **stack_b)
{
	sa(stack_a);
	sb(stack_b);
}
