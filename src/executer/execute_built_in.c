/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_built_in.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/08 11:51:23 by spanfilo      #+#    #+#                 */
/*   Updated: 2025/05/08 11:56:35 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int is_builtin_cmd(char **command_args)
{
	if (!command_args[0])
		return(0);
	if (ft_strncmp(command_args[0],"export", 7) == 0)
		return (1);
	if (ft_strncmp(command_args[0],"env", 4) == 0)
		return (1);
	if (ft_strncmp(command_args[0],"unset", 6) == 0)
		return (1);
	if (ft_strncmp(command_args[0],"exit", 5) == 0)
		return (1);
	if (ft_strncmp(command_args[0],"cd", 3) == 0)
		return (1);
	if (ft_strncmp(command_args[0],"echo", 5) == 0)
		return (1);
	if (ft_strncmp(command_args[0],"pwd", 4) == 0)
		return (1);
	return (0);
}

void execute_builtin(char **command_args, t_minishell *mshell)
{
	if (ft_strncmp(command_args[0], "export", 7) == 0)
		exec_export(command_args, mshell);
	else if (ft_strncmp(command_args[0],"env", 4) == 0)
		exec_env(command_args, mshell);
	else if (ft_strncmp(command_args[0],"unset", 6) == 0)
		exec_unset(command_args, mshell);
	else if (ft_strncmp(command_args[0],"exit", 5) == 0)
		exec_exit(command_args, mshell);
	else if (ft_strncmp(command_args[0],"cd", 3) == 0)
		exec_cd(command_args, mshell);
	else if (ft_strncmp(command_args[0],"pwd", 4) == 0)
		exec_pwd(command_args, mshell);
	else if (ft_strncmp(command_args[0],"echo", 5) == 0)
		exec_echo(command_args, mshell);
}
