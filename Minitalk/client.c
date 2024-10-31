/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:05:38 by jans              #+#    #+#             */
/*   Updated: 2024/10/31 17:21:04 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(int pid, char c)
{
	int				i;
	unsigned char	temp_char;

	i = 8;
	temp_char = c;
	while (i-- > 0)
	{
		temp_char = c >> i;
		if (temp_char % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(30);
	}
}

void	send_string(int pid, const char *str)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(str))
		send_char(pid, str[i++]);
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
	send_string(pid, argv[2]);
	return (0);
}
