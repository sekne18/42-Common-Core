/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:43:31 by jans              #+#    #+#             */
/*   Updated: 2024/11/01 18:00:17 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_sigusr(int sig)
{
	static unsigned char	current_data;
	static int				bit_position;

	current_data |= (sig == SIGUSR1);
	bit_position++;
	if (bit_position == 8)
	{
		if (current_data == '\0')
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd(current_data, 1);
		current_data = 0;
		bit_position = 0;
	}
	else
		current_data <<= 1;
}

int	main(void)
{
	ft_putstr_fd(ft_itoa(getpid()), 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, handle_sigusr);
	signal(SIGUSR2, handle_sigusr);
	while (1)
		pause();
	return (0);
}
