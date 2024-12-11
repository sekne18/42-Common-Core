#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

int	builtin(char *cmd, char *arg, char **envp, char	option);
int	exec_cd(char *arg);
int	exec_pwd();
int	exec_echo(char	*arg, char option);
int	exec_export();
int	exec_unset();
int	exec_env();
int	exec_exit();

#endif
