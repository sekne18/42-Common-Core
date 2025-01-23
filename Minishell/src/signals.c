/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:38:22 by jsekne            #+#    #+#             */
/*   Updated: 2025/01/09 09:43:32 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signals(void)
{
	struct sigaction	sa_c;
	struct sigaction	sa_q;

	sa_c.sa_handler = handle_sigint;
	sa_c.sa_flags = SA_RESTART;
	sigemptyset(&sa_c.sa_mask);
	sigaction(SIGINT, &sa_c, NULL);
	sa_q.sa_handler = SIG_IGN;
	sa_q.sa_flags = SA_RESTART;
	sigemptyset(&sa_q.sa_mask);
	sigaction(SIGQUIT, &sa_q, NULL);
}

void	reset_signals_in_child(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	ignore_signals_in_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
