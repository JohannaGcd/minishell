/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_built_in.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/15 10:04:20 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/15 10:06:33 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	execute_builtin(char **args, t_minishell *mshell, int *exit_status)
{
	if (ft_strncmp(args[0], "export", 7) == 0)
		exec_export(args, mshell);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		exec_env(args, mshell);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		exec_unset(args, mshell);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		exec_exit(args, mshell, exit_status);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		exec_cd(args, mshell);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		exec_pwd(args, mshell);
	else if (ft_strncmp(args[0], "echo", 5) == 0)
		exec_echo(args, mshell);
}
