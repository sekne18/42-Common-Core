/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:28:12 by jans              #+#    #+#             */
/*   Updated: 2024/10/19 21:50:47 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_list **stack_a)
{
	ft_putstr_fd("sa\n", 1);
	swap(stack_a);
}

void	sb(t_list **stack_b)
{
	ft_putstr_fd("sb\n", 1);
	swap(stack_b);
}

void	ss(t_list **stack_a, t_list **stack_b)
{
	swap(stack_a);
	swap(stack_b);
	ft_putstr_fd("ss\n", 1);
}

void	swap(t_list **stack)
{
	t_list	*curr;
	int		tmp_num;
	int		tmp_idx;

	curr = *stack;
	if (!curr || !curr->next)
		return ;
	tmp_num = curr->number;
	tmp_idx = curr->index;
	curr->number = curr->next->number;
	curr->index = curr->next->index;
	curr->next->number = tmp_num;
	curr->next->index = tmp_idx;
}
