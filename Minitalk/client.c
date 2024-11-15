/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:05:38 by jans              #+#    #+#             */
/*   Updated: 2024/11/10 15:47:32 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	response_handler(int signum)
{// Makes sure that client/server wait for each other
	static int	received = 0;

	if (signum == SIGUSR1)
		received++;
	else
	{
		ft_putnbr_fd(received, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

void	send_char(int pid, char c)
{
	int				i;
	unsigned char	temp_char;

	i = 8;
	temp_char = c;
	while (i--)
	{
		if (temp_char >> i & 1) //Shift right by i bits, and compares if equals to 1
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
	}
}

void	send_string(int pid, const char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
		send_char(pid, str[i++]);
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_putstr_fd(argv[0], 1);
		return (1);
	}
	pid = atoi(argv[1]);
	if (pid <= 0)
	{
		ft_putstr_fd("Invalid server PID\n", 1);
		return (1);
	}
	signal(SIGUSR1, response_handler);
	signal(SIGUSR2, response_handler);
	send_string(pid, argv[2]);
	//while (1)
	//	pause();
	return (0);
}
