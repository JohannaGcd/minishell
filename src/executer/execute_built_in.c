/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_built_in.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/15 10:04:20 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/22 18:27:42 by jguacide      ########   odam.nl         */
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

int	save_fd(int fd)
{
	int	saved_fd;

	saved_fd = dup(fd);
	if (saved_fd == -1)
		exit(EXIT_FAILURE);
	return (saved_fd);
}

void	execute_if_builtin(t_command *cmd, t_minishell *mshell,
	int *exit_status)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdout = 0;
	saved_stdin = 0;
	if (cmd->in)
		saved_stdin = save_fd(STDIN_FILENO);
	if (cmd->out)
		saved_stdout = save_fd(STDOUT_FILENO);
	io_redirect(cmd);
	execute_builtin(cmd->command_args, mshell, exit_status);
	if (saved_stdout != 0)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	if (saved_stdin != 0)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}
