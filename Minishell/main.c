/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:56:43 by jsekne            #+#    #+#             */
/*   Updated: 2024/12/11 14:20:33 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	main(int ac, char **av, char **envp)
{
	//create static list of commands
	// 1. Built-ins
	// 2. Add cat to build-ins
	// 2. redirections (dup, dup2)
	// 3. external commands (fork, execve and wait)
	// 4. Add pipes
	char	*input;
	char	*cmd;
	char	*arg;
	int		status;
	(void)ac;
	(void)av;

	while (1)
	{
		input = readline("minishell: ");
		add_history(input);
		cmd = strtok(input, " ");//TODO replace with ft_split	
		arg = strtok(NULL, "\0");//TODO replace with ft_split	
		if (!strcmp(cmd, "echo") || !strcmp(cmd, "cd") ||
        		!strcmp(cmd, "pwd") || !strcmp(cmd, "export") ||
        		!strcmp(cmd, "unset") || !strcmp(cmd, "env") ||
        		!strcmp(cmd, "exit"))
			status = builtin(cmd, arg, envp, ' ');
//		else if ()
		if ((!input || status == -1) == 1) {
            free(input);
            break;
        }
		free(input);
	}
	return (0);
}

int	builtin(char *cmd, char *arg, char **envp, char	option)
{
	int	return_code;

	return_code = 1;
	if (!strcmp(cmd, "cd"))
		return_code = exec_cd(arg);
	else if (!strcmp(cmd, "echo"))
		return_code = exec_echo(arg, option);
	else if (!strcmp(cmd, "pwd"))
		return_code = exec_pwd();
	else if (!strcmp(cmd, "export"))
		return_code = exec_export();
	else if (!strcmp(cmd, "unset"))
		return_code = exec_unset();
	else if (!strcmp(cmd, "env"))
		return_code = exec_env(envp);
	else if (!strcmp(cmd, "exit"))
		exit(0);
	else	
		printf("There was an error in built-ins!\n");
	return (return_code);
}

int	exec_cd(char *arg)
{
	if (!arg)
		return (1);
	if (chdir(arg) != 0)
		return (1);
	return (0);
}

int	exec_pwd()
{
	char cwd[100];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	} 
	else
		return (1);
}

int	exec_echo(char	*arg, char option)
{
	int i;
	int newline;

	newline = 1;
	i = 0;
	if (arg && option == 'n')//TODO use ft_strcmp
		newline = 0;
	if (!arg)
		return (0);
	if (arg[0] == '"')
		arg++;
	if (arg[strlen(arg)-1] == '"')
		arg[strlen(arg)-1] = 0;
	printf("%s", arg);
	if (newline)
		printf("\n");
	return (0);
}

int	exec_export()
{
	//setenv to update value
	return (0);
}

int	exec_unset()
{
	return (0);
}

int	exec_env(char **envp)
{
	int		i;
	char	**env;

	i = -1;
	env = envp;//TODO check for envp??
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);	
}

int	exec_exit()
{
	exit(0);
}
