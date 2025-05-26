/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_built_in.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/15 10:04:20 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/26 14:32:30 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	handle_builtin(t_command *curr_cmd, t_minishell *mshell,
	int *exit_status)
{
	execute_builtin(curr_cmd->command_args, mshell, exit_status);
	exit(EXIT_SUCCESS);
}

// Launches the execution of the appropriate built-in command
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

// Saves the fd before dup2 redirects
int	save_fd(int fd)
{
	int	saved_fd;

	saved_fd = dup(fd);
	if (saved_fd == -1)
		exit(EXIT_FAILURE);
	return (saved_fd);
}

// Handles redirections of STDIN/OUT for built-in commands.
void	redirect_for_builtin(t_command *cmd, t_minishell *mshell,
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
	if (io_redirect(cmd, mshell) == 1)
	{
		mshell->envs->status = 1;
		exit(EXIT_FAILURE);
	}
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
