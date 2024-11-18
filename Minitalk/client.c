/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:05:38 by jans              #+#    #+#             */
/*   Updated: 2024/11/18 14:29:00 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_string(int pid_init, char *str)
{
	static int		current_bit = 0;
	static pid_t	pid = 0;
	static char		*message = NULL;
	int				signal;
	int				zeroes;

	if (pid_init)
		pid = pid_init;
	if (str)
		message = str;
	if (current_bit % 8 == 0)
		zeroes = 0;
	if (message[current_bit / 8] & (0x01 << (current_bit % 8)))
		signal = SIGUSR1;
	else
	{
		signal = SIGUSR2;
		zeroes++;
	}
	current_bit++;
	usleep(128);
	if (kill(pid, signal) || zeroes == 8)
		exit(0);
}

void	response_handler(int signum)
{
	if (signum == SIGUSR2)
		send_string(0, NULL);
	if (signum == SIGUSR1)
		exit(-1);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putstr_fd(argv[0], 1);
		return (1);
	}
	if (atoi(argv[1]) <= 0)
	{
		ft_putstr_fd("Invalid server PID\n", 1);
		return (1);
	}
	signal(SIGUSR1, &response_handler);
	signal(SIGUSR2, &response_handler);
	send_string(atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
