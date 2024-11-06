/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:44:07 by jans              #+#    #+#             */
/*   Updated: 2024/11/05 09:36:30 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->table->write_mutex);
	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
		&& !sim_done(philo->table))
		printf("%-6ld  %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status && !sim_done(philo->table))	
		printf("%-6ld  %d is eating\n", elapsed, philo->id);
	else if (DIED == status)	
		printf("%-6ld  %d died\n", elapsed, philo->id);
	else if (THINKING == status && !sim_done(philo->table))	
		printf("%-6ld  %d is thinking\n", elapsed, philo->id);
	else if (SLEEPING == status && !sim_done(philo->table))	
		printf("%-6ld  %d is sleeping\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
