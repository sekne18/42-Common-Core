/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:59:11 by jans              #+#    #+#             */
/*   Updated: 2024/10/20 13:37:10 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	1) Handles the inputs the same way as mandatory
	2) reads instructions followed by '\n 'from standard input
	3) Executes instruciton and returns "KO" or "OK"
	Return "Error" if anything way wrong*
*/

void	main(int argc, char **argv)
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
	if (validate_instructions())
	ft_lstclear(&stack_a);
	return (1);
}
