/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:48:38 by jans              #+#    #+#             */
/*   Updated: 2024/10/17 15:04:43 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	validate_args(int argc, char **argv, t_list **stack)
{
	int		i;
	int		type;
	int		ret;

	type = 1;
	if (argc == 2)
	{
		type--;
		argv = ft_split(argv[argc - 1], ' ');
	}
	i = ft_arrlen(argv);	
	ret = fill_list(i, type, stack, argv); 
	if (!type)
		free_all(argv);
	return (ret);
}

int	fill_list(int len, int type, t_list **stack, char **argv)
{
	t_list	*node;
	int		i;

	i = type - 1;
	while (len > ++i)
	{
		if (!valid_arg_format(argv[i]))
			return (0);
		node = ft_lstnew(ft_atoi(argv[i]));
		if (!node)
			return (0);
		ft_lstadd_back(stack, node);
		if (has_duplicates(stack, node))
			return (0);
	}
	return (1);
}

int	ft_arrlen(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

int	has_duplicates(t_list **stack, t_list *node)
{
	t_list	*curr;

	curr = *stack;
	while (curr->next)
	{
		if (curr->number == node->number)
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	valid_arg_format(char *str)
{
	int		i;
	int		op;

	op = 0;
	i = -1;
	while (str[++i] == '-' || str[i] == '+')
		op++;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	if (INT_MAX < ft_atoi(str) || INT_MIN > ft_atoi(str))
		return (0);
	return (op < 2);
}
