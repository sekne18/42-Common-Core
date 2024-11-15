/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:43:31 by jans              #+#    #+#             */
/*   Updated: 2024/11/10 15:24:09 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


void	handle_sigusr(int signum, siginfo_t *info, void *context)
{
	static	char	current_data = 0;
	static	int		bit_position = 0;
	static	pid_t	client_pid = 0;

	(void)context;
	if (!client_pid) // If no client has been assigned
		client_pid = info->si_pid; // assigns the sending process's PID
	current_data |= (signum == SIGUSR2); // Is condition is true, sets 1, otherwise 0
	if (++bit_position == 8)
	{
		bit_position = 0; // reset
		if (!current_data)
		{
			kill(client_pid, SIGUSR2); // Indicates the end of messages
			client_pid = 0; // reset
			return ;
		}
		ft_putchar_fd(current_data, 1); //print character
		current_data = 0; // reset
		// signals back that it has successfully received and printed a character
		kill(client_pid, SIGUSR1); 
	}
	else
		current_data <<= 1; // shift one bit to the left, prep to receive the next bit
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr_fd(ft_itoa(getpid()), 1);
	ft_putchar_fd('\n', 1);
	// Will pass extra info (the info and context) to the handler
	sa.sa_flags = SA_SIGINFO; 
	sa.sa_sigaction = &handle_sigusr;
	sigaction(SIGUSR1, &sa, NULL); // Assign handler
	sigaction(SIGUSR2, &sa, NULL); // Assign handler
	while (1)
		pause();
	return (0);
}
