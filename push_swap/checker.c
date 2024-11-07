/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:59:11 by jans              #+#    #+#             */
/*   Updated: 2024/11/06 08:20:57 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc < 2)
		return (1);
	if (!validate_args(argc, argv, &stack_a))
	{
		ft_putstr_fd("Error\n", 1);
		ft_lstclear(&stack_a);
		return (0);
	}
	if (!is_sorted(stack_a))
		read_instructions(&stack_a, &stack_b);
	if (stack_a)
		ft_lstclear(&stack_a);
	if (stack_b)
		ft_lstclear(&stack_b);
	return (1);
}

int	read_instructions(t_list **stack_a, t_list **stack_b)
{
	char	str[4];
	int		flag;
	int		i;
	int		bytes_read;

	i = 0;
	flag = 0;
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(0, &str, 4);
		if ((flag && ft_strchr(str, '\n')) || bytes_read == 0)
			break ;
		if (flag)
			continue ;
		str[bytes_read-1] = 0;
		if (!execute(str, stack_a, stack_b))
			flag = 1;
		ft_bzero(str, 4);
	}
	if (flag)
		return (0);
	print_list(stack_a);
	if (is_sorted(*stack_a) && !*stack_b)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
	return (1);
}

int	execute(char *str, t_list **stack_a, t_list **stack_b)
{
	//if (*str != '\n')
	//	return (1);
	if (!valid(str, stack_a, stack_b))
	{
		ft_putstr_fd("Error\n", 0);
		return (0);
	}
	return (1);
}

int	valid(char	*str, t_list **stack_a, t_list **stack_b)
{
	if (ft_strncmp(str, "sa", 3) == 0)
		sa(stack_a, 1);
	else if (ft_strncmp(str, "sb", 3) == 0)
		sb(stack_b, 1);	
	else if (ft_strncmp(str, "ss", 3) == 0)
		ss(stack_a, stack_b, 1);
	else if (ft_strncmp(str, "pa", 3) == 0)
		pa(stack_a, stack_b, 1);
	else if (ft_strncmp(str, "pb", 3) == 0)
		pb(stack_a, stack_b, 1);
	else if (ft_strncmp(str, "ra", 3) == 0)
		ra(stack_a, 1);
	else if (ft_strncmp(str, "rb", 3) == 0)
		rb(stack_b, 1);
	else if (ft_strncmp(str, "rr", 3) == 0)
		rr(stack_a, stack_b, 1);
	else if (ft_strncmp(str, "rra", 3) == 0)
		rra(stack_a, 1);
	else if (ft_strncmp(str, "rrb", 3) == 0)
		rrb(stack_b, 1);
	else if (ft_strncmp(str, "rrr", 3) == 0)
		rrr(stack_a, stack_b, 1);
	else
		return (0);
	return (1); 
}
