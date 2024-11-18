/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:43:31 by jans              #+#    #+#             */
/*   Updated: 2024/11/18 14:28:34 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_sigusr(int signum, siginfo_t *info, void *context)
{
	static	char	curr_data = 0;
	static	int		bits_received = 0;

	(void)context;
	if (signum == SIGUSR1)
	{
		curr_data = curr_data | (0x01 << bits_received % 8);
	}
	if (bits_received % 8 == 7)
	{
		if (curr_data == '\0')
		{
			usleep(256);
			kill(info->si_pid, SIGUSR1);
		}
		else
			write(1, &curr_data, 1);
		curr_data = 0; // reset
	}
	bits_received++;	
	usleep(256);
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			block_mask;

	ft_putstr_fd("PID: " , 1);
	ft_putstr_fd(ft_itoa(getpid()), 1);
	ft_putchar_fd('\n', 1);
	sigemptyset(&block_mask);	
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	sa.sa_handler = 0;
	sa.sa_flags = SA_SIGINFO; 
	sa.sa_mask = block_mask;
	sa.sa_sigaction = &handle_sigusr;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		write(1, "Error", 5);
		return (0);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(1, "Error", 5);
		return (0);
	}
	while (1)
		pause();
	return (0);
}
