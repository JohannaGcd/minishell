#include "executer.h"

void execute_builtin(char **command_args, t_minishell *mshell, int *exit_status)
{
	if (ft_strncmp(command_args[0], "export", 7) == 0)
		exec_export(command_args, mshell);
	else if (ft_strncmp(command_args[0],"env", 4) == 0)
		exec_env(command_args, mshell);
	else if (ft_strncmp(command_args[0],"unset", 6) == 0)
		exec_unset(command_args, mshell);
	else if (ft_strncmp(command_args[0],"exit", 5) == 0)
		exec_exit(command_args, mshell, exit_status);
	else if (ft_strncmp(command_args[0],"cd", 3) == 0)
		exec_cd(command_args, mshell);
	else if (ft_strncmp(command_args[0],"pwd", 4) == 0)
		exec_pwd(command_args, mshell);
	else if (ft_strncmp(command_args[0],"echo", 5) == 0)
		exec_echo(command_args, mshell);
}