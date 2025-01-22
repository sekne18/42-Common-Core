/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 01:11:32 by jans              #+#    #+#             */
/*   Updated: 2025/01/15 10:12:13 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signum)
{
	(void)signum;
	g_signals = g_signals | S_CTRL_C;
	write(STDIN_FILENO, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	if (g_signals & S_HEREDOC)
		close(STDIN_FILENO);
	else
		rl_redisplay();
}

void	handle_sigquit(int signum)
{
	(void)signum;
}

void	handle_ctrl_d(char *line, t_context *context)
{
	(void)context;
	if (!line)
	{
		destroy_dyn_arr(context->envp, NULL);
		exit(0);
	}
}
