/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:55:24 by jans              #+#    #+#             */
/*   Updated: 2024/10/17 15:54:58 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	radix_sort(t_list **stack_a, t_list **stack_b)
{

	ft_putstr_fd("INITIALIZED:\n", 1);
	print_list(*stack_a);
	print_list(*stack_b);
	
	sa(stack_a);
	ft_putstr_fd("sa\n", 1);
	print_list(*stack_a);
	print_list(*stack_b);
	
	sb(stack_b);
	ft_putstr_fd("sb\n", 1);
	print_list(*stack_a);
	print_list(*stack_b);
	
	ss(stack_a, stack_b);
	ft_putstr_fd("ss\n", 1);
	print_list(*stack_a);
	print_list(*stack_b);

	pb(stack_a, stack_b);
	ft_putstr_fd("pb\n", 1);
	print_list(*stack_a);
	print_list(*stack_b);

	pa(stack_a, stack_b);
	ft_putstr_fd("pa\n", 1);
	print_list(*stack_a);
	print_list(*stack_b);
	
	ra(stack_a);
	ft_putstr_fd("ra\n", 1);
	print_list(*stack_a);
	print_list(*stack_b);
	
	rb(stack_b);
	ft_putstr_fd("rb\n", 1);
	print_list(*stack_a);
	print_list(*stack_b);

	rr(stack_a, stack_b);
	ft_putstr_fd("rr\n", 1);
	print_list(*stack_a);
	print_list(*stack_b);
	
	rra(stack_a);
	ft_putstr_fd("rra\n", 1);
	print_list(*stack_a);
	print_list(*stack_b);
	
	rrb(stack_b);
	ft_putstr_fd("rrb\n", 1);
	print_list(*stack_a);
	print_list(*stack_b);
	
	rrr(stack_a, stack_b);
	ft_putstr_fd("rrr\n", 1);
	print_list(*stack_a);
	print_list(*stack_b);
}
